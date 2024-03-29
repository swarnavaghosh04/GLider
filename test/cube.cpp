#include <cmath>
#include <vector>
#include <array>
#include <cstdio>
#include <iostream>
#include <filesystem>

#include "GLider/GLider.hpp"
#include "util.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

// Rotations Characteristics ==================================================

// Number of Key hits for a 360 Degree rotation about an axis (multiple of 8)
#define KEYHITS_PER_ROTATION 40

// This is a test

static_assert(
    KEYHITS_PER_ROTATION % 8 == 0,
    "Key hits per rotation should be a multiple of 8"
);

/* If the difference between the desired and current rotation is
below this value, then actual is set equal to desired */
#define ROTATION_CLAMP_THRESHOLD    0.01f

/* The time (in seconds) for a rotation to converge
to its desired rotation after one key hit.
In other words, the cube will be in motion for
this many seconds after a key is pressed once. */
#define ROTATION_CONVERGENCE_TIME      1.f

// Macors ======================================================================

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#define PI2 (2.f*(float)M_PI)
#define PI_4 ((float)M_PI/4.f)
// Structures For Data Organization ============================================

struct MotionVar{

    struct Bounds{float min, max;};

    float desired;
    float actual;
    const Bounds& pBounds;

    MotionVar(float val, const Bounds& pBounds = {0,0}):
        desired{val},
        actual{val},
        pBounds{pBounds}
    {}

    inline float distanceBetweenBounds(){return (pBounds.max)-(pBounds.min);}

    void incrementDesired(){
        desired += 1;
        if(pBounds.max != 0 && desired >= pBounds.max){
            desired -=  distanceBetweenBounds();
            actual -= distanceBetweenBounds();
        }
    }

    void decrementDesired(){
        desired -= 1;
        if(pBounds.min != 0 && desired <= pBounds.min){
            desired += distanceBetweenBounds();
            actual += distanceBetweenBounds();
        }
    }

};

struct MotionVector3D{

    MotionVar x, y, z;
    const MotionVar::Bounds& pBounds;
    float rotFactor = 0;

    MotionVector3D(float x, float y, float z, const MotionVar::Bounds& pBounds = {0,0}):
        x{x, pBounds},
        y{y, pBounds},
        z{z, pBounds},
        pBounds{pBounds}
    {}

    MotionVector3D(glm::vec3 v, const MotionVar::Bounds& pBounds = {0,0}):
        x{v.x, pBounds},
        y{v.y, pBounds},
        z{v.z, pBounds},
        pBounds{pBounds}
    {}

    glm::vec3 getCurrent() const {return glm::vec3(x.actual, y.actual, z.actual);}
    glm::vec3 getDesired() const {return glm::vec3(x.desired, y.desired, z.desired);}
    void reset(float x=0, float y=0, float z=0) {
        this->x.desired = x;
        this->y.desired = y;
        this->z.desired = z;
    }

    void computeMotion(){

        float delta;

        auto update = [&](MotionVar& m){ m.actual += rotFactor*delta; };
        
        auto manageComponent = [&](MotionVar& m){
            delta = m.desired - m.actual;
            if(std::abs(delta) > ROTATION_CLAMP_THRESHOLD) update(m);
            else m.actual = m.desired;
        };

        manageComponent(x);
        manageComponent(y);
        manageComponent(z);
    }

};

struct Cube{

    std::array<float,3*8>            vertexBufData;
    std::array<unsigned char, 6*6>   indexBufData;

    gli::VertexArray                        vertexArray;
    gli::Buffer<gli::VertexBuffer>          vertexBuffer;
    gli::Buffer<gli::IndexBuffer>           indexBuffer;
    gli::ShaderProgram                            shaders;

    const MotionVar::Bounds translationBounds;
    const MotionVar::Bounds rotationBounds;

    MotionVector3D observerPosition;
    MotionVector3D observerForwards;
    MotionVector3D observerUpwards;
    MotionVector3D rotationState;
    MotionVar theta;

    template <std::size_t N1, std::size_t N2>
    static void generateVertices(
        float sideLength,
        const glm::vec3& center,
        std::array<float,N1>& vertexOutputBuffer,
        std::array<unsigned char, N2>& indexOutputBuffer
    ){
        float sideLength_half = sideLength/2.f; 

        glm::vec2 a(center.x-sideLength_half, center.x+sideLength_half);
        glm::vec2 b(center.y-sideLength_half, center.y+sideLength_half);
        glm::vec2 c(center.z-sideLength_half, center.z+sideLength_half);

        {
            const float vertices[3*8] = {
                a.x, b.x, c.x,
                a.x, b.x, c.y,
                a.x, b.y, c.y,
                a.x, b.y, c.x,
                a.y, b.x, c.x,
                a.y, b.x, c.y,
                a.y, b.y, c.y,
                a.y, b.y, c.x,
            };
            memcpy(vertexOutputBuffer.data(), vertices, sizeof(vertices));

        }{
            const unsigned char indices[6*6] = {
                0, 1, 3, 1, 3, 2,
                6, 5, 7, 5, 7, 4,
                1, 0, 5, 0, 5, 4,
                2, 3, 6, 3, 6, 7,
                0, 3, 4, 3, 4, 7,
                2, 1, 6, 1, 6, 5
            };
            memcpy(indexOutputBuffer.data(), indices, sizeof(indices));
        }
    }

    Cube(std::filesystem::path exepath):
        translationBounds{-50.f, 50.f},
        rotationBounds{-KEYHITS_PER_ROTATION/2, KEYHITS_PER_ROTATION/2},
        observerPosition{ 0.f, 0.f, 5.f, translationBounds},
        observerForwards{ 0.f, 0.f, -1.f, translationBounds},
        observerUpwards{ 0.f, 1.f, 0.f, translationBounds},
        rotationState{ 0.f,  0.f, 0.f, rotationBounds},
        theta{0, {0.f, 2.f*3.14159f}}
    {
        GLI_PRINT_DEBUG("Cube Init\n");
        generateVertices(1, glm::vec3(0,0,0), vertexBufData, indexBufData);
        vertexBuffer.feedData(vertexBufData, gli::UseStaticDraw);
        indexBuffer.feedData(indexBufData, gli::UseStaticDraw);
        gli::Layout verBufLayout(1);
        verBufLayout.push<float>(gli::D3, false);
        vertexArray.readBufferData(vertexBuffer, verBufLayout);
        auto res = exepath / "../share/GLider/test/";
        shaders.compileFile(gli::VertexShader, (res / "cube.vs").string().c_str());
        shaders.compileFile(gli::FragmentShader, (res / "cube.fs").string().c_str());
        shaders.link();
        shaders.validate();
        shaders.bind();
        shaders.bindAttribLocation(0, "position");
        vertexArray.bind();
        indexBuffer.bind();
    }

    void draw()
    {
        int drawCounter = 0;

        vertexArray.bind();

        auto draw_square_with_color = [&](const glm::vec4& v){

            shaders.setUniform("u_color", v);
            indexBuffer.draw<unsigned char>(
                gli::DrawTriangles,
                6,
                drawCounter);
            drawCounter += 6;
            indexBuffer.draw<unsigned char>(
                gli::DrawTriangles,
                6,
                drawCounter);
            drawCounter += 6;

        };

        draw_square_with_color(glm::vec4(1.0, 0.0, 0.0, 1.0));
        draw_square_with_color(glm::vec4(0.0, 1.0, 0.0, 1.0));
        draw_square_with_color(glm::vec4(0.0, 0.0, 1.0, 1.0));   
    }

};

int main(int argc, char* argv[]){

    (void)argc;

    try{

        SDL sdl(3,1);
        
        SDL_DisplayMode dm;

        if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
            throw std::runtime_error(SDL_GetError());

        int q = std::min(dm.h, dm.w) * 3.f/4.f;
        dm.h = dm.w = q;

        SDL::OpenGLWindow window{"Cube", dm.w, dm.h};

        gli::initialize(SDL_GL_GetProcAddress);
        
        GLI_PRINT_DEBUG("GLVerion: %d.%d\n", GLVersion.major, GLVersion.minor);

        auto exepath = std::filesystem::path(argv[0]).remove_filename();
        Cube cube(exepath);

        GLI_PRINT_DEBUG("Cube Created\n");

        {
            int buffers, samples;
            SDL_GL_GetAttribute( SDL_GL_MULTISAMPLEBUFFERS, &buffers );
            SDL_GL_GetAttribute( SDL_GL_MULTISAMPLESAMPLES, &samples );
            GLI_PRINT_DEBUG("buf = %d, samples = %d\n", buffers, samples);
        }

        // Setup MVP =============================

        glm::mat4 mvp, projection = 
            glm::perspective(70.f*3.14159f/180.f, (float)dm.w/(float)dm.h, 0.001f, 1000.f);

        gli::enable(gli::Capability_NI::DepthTest);
        gli::depthRange(0.01, 1000.0);

        bool keepRunning = true;
        SDL_Event event;

        gli::FrameRate fps;
        auto fps_print = std::chrono::steady_clock::now();

        /* Loop until the user closes the window */
        while (keepRunning)
        {

            // Compute motion ===========

            cube.rotationState.computeMotion();
            cube.observerPosition.computeMotion();

            mvp =
                projection*
                glm::lookAt(
                    cube.observerPosition.getCurrent(),
                    cube.observerPosition.getCurrent() + cube.observerForwards.getCurrent(),
                    cube.observerUpwards.getCurrent()
                );

            cube.shaders.setUniform("u_mat", mvp, false);
            cube.shaders.setUniform("orientation", glm::vec3(
                (PI2/KEYHITS_PER_ROTATION)*(cube.rotationState.x.actual)+(PI_4),
                (PI2/KEYHITS_PER_ROTATION)*(cube.rotationState.y.actual)+(PI_4),
                (PI2/KEYHITS_PER_ROTATION)*(cube.rotationState.z.actual)+(0)
            ));

            /* Render here */
            gli::clear(gli::ColorBufferBit | gli::DepthBufferBit);

            cube.draw();

            /* Swap front and back buffers */
            window.swap();

            /* Poll for and process events */
            while(SDL_PollEvent(&event)){
                
                #define shiftModifiersActived event.key.keysym.mod & KMOD_SHIFT

                switch(event.type){
                case SDL_QUIT:
                    keepRunning = false;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                    case SDLK_LEFT:
                        if(shiftModifiersActived)
                            cube.observerPosition.x.decrementDesired();
                        else
                            cube.rotationState.y.decrementDesired();
                        break;
                    case SDLK_RIGHT:
                        if(shiftModifiersActived)
                            cube.observerPosition.x.incrementDesired();
                        else
                            cube.rotationState.y.incrementDesired();
                        break;
                    case SDLK_UP:
                        if(shiftModifiersActived)
                            cube.observerPosition.y.incrementDesired();
                        else
                            cube.rotationState.x.decrementDesired();
                        break;
                    case SDLK_DOWN:
                        if(shiftModifiersActived)
                            cube.observerPosition.y.decrementDesired();
                        else
                            cube.rotationState.x.incrementDesired();
                        break;
                    case SDLK_PERIOD:
                        if(shiftModifiersActived)
                            cube.observerPosition.z.incrementDesired();
                        else
                            cube.rotationState.z.decrementDesired();
                        break;
                    case SDLK_COMMA:
                        if(shiftModifiersActived)
                            cube.observerPosition.z.decrementDesired();
                        else
                            cube.rotationState.z.incrementDesired();
                        break;
                    case SDLK_w:
                        cube.theta.desired += 3.14159/18.f; // + 10 degrees
                        break;
                    case SDLK_s:
                        cube.theta.desired -= 3.14159/18.f; // - 10 degrees
                        break;
                    case SDLK_SPACE:
                        if(shiftModifiersActived){
                            cube.observerPosition.reset(0,0,5);
                        }else{
                            cube.rotationState.reset();
                        }
                        break;
                    case SDLK_ESCAPE:
                        keepRunning = false;
                        break;
                    }
                    break;
                }

                #undef shiftModifiersActived

            } // while(SDL_PollEvent(&event))

            fps.compute();

            // Compute Rotation Rate ===============
            cube.observerPosition.rotFactor =
            cube.rotationState.rotFactor =
            (std::log(1.f/ROTATION_CLAMP_THRESHOLD)/ROTATION_CONVERGENCE_TIME)/fps();

            cube.theta.actual += (cube.theta.desired - cube.theta.actual)/fps();

            if(
                float timePassed = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - fps_print
                ).count();
                timePassed >= 500
            ){
                std::printf(
                    "fps: %5.0f\r",
                    fps()
                );
                fps_print = std::chrono::steady_clock::now();
            }
            
            
        } // while(keepRunning)

    }catch(const std::exception& ex){
        std::printf("%s occured!\n", typeid(ex).name());
        std::printf("%s", ex.what());
    }

    return 0;

}