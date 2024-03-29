#include "GLider/GLider.hpp"
#include <cmath>
#include <vector>
#include <array>
#include <cstdio>

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

    static constexpr const char* const vertexShader = R"CODE(
        #version 140

        in vec3 position;

        uniform mat4 u_mat;
        uniform vec3 orientation;
        // uniform float theta;

        vec4 quat_mult(vec4 a, vec4 b)
        {
            return vec4(
                ((a.w*b.x) + (a.x*b.w) + (a.y*b.z) - (a.z*b.y)), // x
                ((a.w*b.y) - (a.x*b.z) + (a.y*b.w) + (a.z*b.x)), // y
                ((a.w*b.z) + (a.x*b.y) - (a.y*b.x) + (a.z*b.w)), // z
                ((a.w*b.w) - (a.x*b.x) - (a.y*b.y) - (a.z*b.z))  // w
            );
        }

        vec4 quat_conj(vec4 q)
        {
            return vec4(-q.x, -q.y, -q.z, q.w);
        }

        vec4 quat_inv(vec4 q)
        {
            float mag_sqr = q.x*q.x + q.y*q.y + q.z*q.z * q.w*q.w;
            return quat_conj(q)/mag_sqr;
        }

        vec4 quat_rot(float angle, vec3 axis){
            float half_angle = angle/2;
            float sin_half_angle = sin(half_angle);
            return vec4(
                axis.x * sin_half_angle,
                axis.y * sin_half_angle,
                axis.z * sin_half_angle,
                cos(half_angle)
            );
        }

        void main(){

            vec4 pos = vec4(position, 1.f);

            vec4 rotx = quat_rot(orientation.z, vec3(0.f, 0.f, 1.f));
            vec4 roty = quat_rot(orientation.y, vec3(0.f, 1.f, 0.f));
            vec4 rotz = quat_rot(orientation.x, vec3(1.f, 0.f, 0.f));

            vec4 rot = quat_mult(rotz,quat_mult(roty,rotx));

            gl_Position = u_mat * quat_mult(rot,quat_mult(pos, quat_conj(rot)));

        }
    )CODE";

    static constexpr const char* const fragmentShader = R"CODE(
        #version 140

        uniform vec4 u_color;

        void main(){
            gl_FragColor = u_color;
        }
    )CODE";

    std::array<float,3*8>            vertexBufData;
    std::array<unsigned char, 6*6>   indexBufData;

    gli::VertexArray                        vertexArray;
    const std::array<gli::LayoutElement,1>  verBufLayout;
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

    Cube():
        verBufLayout{gli::LayoutElement{gli::D3, gli::Norm_FALSE}},
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
        vertexArray.readBufferData<float>(vertexBuffer, verBufLayout);
        shaders.compileString(gli::VertexShader, vertexShader);
        shaders.compileString(gli::FragmentShader, fragmentShader);
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

constexpr const char* const Cube::vertexShader;
constexpr const char* const Cube::fragmentShader;

void test(){

    #define printSize(x) GLI_PRINT_DEBUG("%-20s: %u \n", #x , (unsigned int)sizeof(x))

    #undef printSize

}

int main(int argc, char* argv[]){

    (void)argc;
    (void)argv[0];

    try{ gli::initialize(3,1); }
    catch(std::exception& ex){
        std::printf("%s occured! Cannot initialize GLider\n", typeid(ex).name());
        std::printf("%s", ex.what());
        return 1;
    }

    try{
        
        SDL_DisplayMode dm;

        if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
            throw std::runtime_error(SDL_GetError());

        int q = std::min(dm.h, dm.w) * 3.f/4.f;
        dm.h = dm.w = q;

        gli::OpenGLWindow window{"Cube", dm.w, dm.h};
        
        GLI_PRINT_DEBUG("GLVerion: %d.%d\n", GLVersion.major, GLVersion.minor);

        Cube cube;

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
                // glm::rotate( (PI2/KEYHITS_PER_ROTATION)*(cube.rotationState.x.actual)+(PI_4) ) *
                // glm::rotate( (PI2/KEYHITS_PER_ROTATION)*(cube.rotationState.y.actual)+(PI_4) ) *
                // glm::rotate( (PI2/KEYHITS_PER_ROTATION)*(cube.rotationState.z.actual)+(0) );

            cube.shaders.setUniform("u_mat", mvp, false);
            cube.shaders.setUniform("orientation", glm::vec3(
                (PI2/KEYHITS_PER_ROTATION)*(cube.rotationState.x.actual)+(PI_4),
                (PI2/KEYHITS_PER_ROTATION)*(cube.rotationState.y.actual)+(PI_4),
                (PI2/KEYHITS_PER_ROTATION)*(cube.rotationState.z.actual)+(0)
            ));
            //cube.shaders.setUniform("theta", glm::vec1(cube.theta.actual));

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

    gli::quit();

    return 0;

}