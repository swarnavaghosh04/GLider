#include "HermyGL/HermyGL.hpp"
#include <cmath>
#include <vector>

#define MY_WINDOW_WIDTH     700
#define MY_WINDOW_HEIGHT    700

// Rotations Characteristics ==================================================

// Number of Key hits for a 360 Degree rotation about an axis
#define KEYHITS_PER_ROTATION        40

/* If the difference between the desired and current rotation is
below this value, then actual is set equal to desired */
#define ROTATION_CLAMP_THRESHOLD    0.01f

/* The time (in seconds) for a rotation to converge
to its desired rotation after one key hit.
In other words, the cube will be in motion for
this many seconds after a key is pressed once. */
#define ROTATION_CONVERGENCE_TIME      1.f

// Macors ======================================================================
#define PI2 (2.f*(float)M_PI)

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

    MotionVar x,y,z;
    const MotionVar::Bounds& pBounds;
    float rotFactor = 0;

    MotionVector3D(float x, float y, float z, const MotionVar::Bounds& pBounds = {0,0}):
        pBounds{pBounds},
        x{x, pBounds},
        y{y, pBounds},
        z{z, pBounds}
    {}

    MotionVector3D(glm::vec3 v, const MotionVar::Bounds& pBounds = {0,0}):
        pBounds{pBounds},
        x{v.x, pBounds},
        y{v.y, pBounds},
        z{v.z, pBounds}
    {}

    glm::vec3 getActual() const {return glm::vec3(x.actual, y.actual, z.actual);}
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
        #version 330 core

        uniform mat4 u_mat;

        layout(location=0) in vec3 position;

        void main(){
            gl_Position = u_mat*vec4(position, 1.f);
        }
    )CODE";

    static constexpr const char* const fragmentShader = R"CODE(
        #version 330 core

        uniform vec4 u_color;

        void main(){
            gl_FragColor = u_color;
        }
    )CODE";

    // If you change the size here, change the size in the constructor as well
    static constexpr hgl::BufferData<float> vertexBufData = {
        8*3,
        (const float[]){
             .5f,  .5f,  .5f,   // 0
            -.5f,  .5f,  .5f,   // 1
            -.5f, -.5f,  .5f,   // 2
             .5f, -.5f,  .5f,   // 3
             .5f,  .5f, -.5f,   // 4
            -.5f,  .5f, -.5f,   // 5
            -.5f, -.5f, -.5f,   // 6
             .5f, -.5f, -.5f    // 7
        }
    };

    // If you change the size here, change the size in the constructor as well
    static constexpr hgl::BufferData<unsigned char> indexBufData = {
        6*6,
        (const unsigned char []){
            0, 1, 3, 1, 3, 2,
            1, 0, 5, 0, 5, 4,
            6, 5, 7, 5, 7, 4,
            2, 3, 6, 3, 6, 7,
            0, 3, 4, 3, 4, 7,
            2, 1, 6, 1, 6, 5
        }
    };

    hgl::VertexArray                vertexArray;
    const hgl::LayoutElement        verBufLayout[1];
    hgl::Buffer<hgl::VertexBuffer>  vertexBuffer;
    hgl::Buffer<hgl::IndexBuffer>   indexBuffer;
    hgl::Shaders                    shaders;


    const MotionVar::Bounds translationBounds;
    const MotionVar::Bounds rotationBounds;

    MotionVector3D observerPosition;
    MotionVector3D observerForwards;
    MotionVector3D observerUpwards;
    MotionVector3D rotationState;

    Cube():
        verBufLayout{{hgl::D3, hgl::Norm_FALSE}},
        translationBounds{-50.f, 50.f},
        rotationBounds{-KEYHITS_PER_ROTATION/2, KEYHITS_PER_ROTATION/2},
        observerPosition{ 0.f, 0.f, 5.f, translationBounds},
        observerForwards{ 0.f, 0.f, -1.f, translationBounds},
        observerUpwards{ 0.f, 1.f, 0.f, translationBounds},
        rotationState{ 0.f,  0.f, 0.f, rotationBounds}
    {
        SDL_Log("Cube Init\n");
        vertexBuffer.feedData<float>(vertexBufData, hgl::UseStaticDraw);
        indexBuffer.feedData<unsigned char>(indexBufData, hgl::UseStaticDraw);
        vertexArray.readBufferData<float>(vertexBuffer, verBufLayout, sizeof(verBufLayout)/sizeof(hgl::LayoutElement));
        shaders.compileString(hgl::VertexShader, vertexShader);
        shaders.compileString(hgl::FragmentShader, fragmentShader);
        shaders.link();
        shaders.validate();
        shaders.use();
        vertexArray.bind();
        indexBuffer.bind();
    }

};

constexpr hgl::BufferData<float> Cube::vertexBufData;
constexpr hgl::BufferData<unsigned char> Cube::indexBufData;
constexpr const char* const Cube::vertexShader;
constexpr const char* const Cube::fragmentShader;

void test(){

    

}

int main(int argc, const char* argv[]){

    test();

    try{

        hgl::initialize();

        {

            hgl::Window window{"Cube", MY_WINDOW_WIDTH, MY_WINDOW_HEIGHT};

            Cube cube;

            SDL_Log("Cube Created\n");

            {
                int buffers, samples;
                SDL_GL_GetAttribute( SDL_GL_MULTISAMPLEBUFFERS, &buffers );
                SDL_GL_GetAttribute( SDL_GL_MULTISAMPLESAMPLES, &samples );
                SDL_Log("buf = %d, samples = %d\n", buffers, samples);
            }

            // Setup MVP =============================

            glm::mat4 mvp, projection = 
                glm::perspective(70.f, (float)MY_WINDOW_WIDTH/MY_WINDOW_HEIGHT, 0.01f, 1000.f);

            // Setup Motion Variables ==========================

            hgl::FrameRate fps;

            GL_CALL(glDepthRange(0.01, 1000));

            bool keepRunning = true;
            SDL_Event event;

            /* Loop until the user closes the window */
            while (keepRunning)
            {

                // Compute motion ===========

                cube.rotationState.computeMotion();
                cube.observerPosition.computeMotion();

                mvp =
                    projection *
                    glm::lookAt(
                        cube.observerPosition.getActual(),
                        cube.observerPosition.getActual() + cube.observerForwards.getActual(),
                        cube.observerUpwards.getActual()
                    ) *
                    glm::rotate( (PI2/KEYHITS_PER_ROTATION)*(cube.rotationState.x.actual+(KEYHITS_PER_ROTATION/8)), glm::vec3(1.f, 0.f, 0.f) ) *
                    glm::rotate( (PI2/KEYHITS_PER_ROTATION)*(cube.rotationState.y.actual+(KEYHITS_PER_ROTATION/8)), glm::vec3(0.f, 1.f, 0.f) ) *
                    glm::rotate( (PI2/KEYHITS_PER_ROTATION)*(cube.rotationState.z.actual+(0)), glm::vec3(0.f, 0.f, 1.f) );

                cube.shaders.setUniform("u_mat", mvp, false);

                /* Render here */
                hgl::clear(hgl::ColorBufferBit);

                cube.shaders.setUniform("u_color", glm::vec4(1.0, 0.0, 0.0, 1.0));
                cube.indexBuffer.draw<unsigned char>(
                    hgl::DrawTriangles,
                    6,
                    6*0);

                cube.shaders.setUniform("u_color", glm::vec4(0.0, 1.0, 0.0, 1.0));
                cube.indexBuffer.draw<unsigned char>(
                    hgl::DrawTriangles,
                    6,
                    6*1);
                
                cube.shaders.setUniform("u_color", glm::vec4(1.0, 0.0, 0.0, 1.0));
                cube.indexBuffer.draw<unsigned char>(
                    hgl::DrawTriangles,
                    6,
                    6*2);
                
                cube.shaders.setUniform("u_color", glm::vec4(0.0, 1.0, 0.0, 1.0));
                cube.indexBuffer.draw<unsigned char>(
                    hgl::DrawTriangles,
                    6,
                    6*3);
                
                cube.shaders.setUniform("u_color", glm::vec4(0.0, 0.0, 1.0, 1.0));
                cube.indexBuffer.draw<unsigned char>(
                    hgl::DrawTriangles,
                    6,
                    6*4);

                cube.shaders.setUniform("u_color", glm::vec4(0.0, 0.0, 1.0, 1.0));
                cube.indexBuffer.draw<unsigned char>(
                    hgl::DrawTriangles,
                    6,
                    6*5);

                /* Swap front and back buffers */
                SDL_GL_SwapWindow(window.getWindow());

                /* Poll for and process events */
                while(SDL_PollEvent(&event)){
                    
                    #define shiftModifiersActived ( event.key.keysym.mod & ( KMOD_LSHIFT | KMOD_RSHIFT ) )

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
                        case SDLK_SPACE:
                            if(shiftModifiersActived){
                                cube.observerPosition.reset(0,0,5);
                            }else{
                                cube.rotationState.reset();
                            }
                            break;
                        }
                        break;
                    }

                    #undef shiftModifiersActived

                } // while(SDL_PollEvent(&event))


                fps.compute();

                // Compute Rotation Rate ===============
                cube.rotationState.rotFactor = (std::log(1.f/ROTATION_CLAMP_THRESHOLD)/ROTATION_CONVERGENCE_TIME)/fps();
                cube.observerPosition.rotFactor = cube.rotationState.rotFactor;

                printf(
                    "fps: %5.0f\n"
                    "\033[1A",
                    fps()
                );
                
            } // while(keepRunning)
        }

        hgl::quit();

    }catch(const std::exception& ex){
        SDL_Log("%s occured!\n", typeid(ex).name());
        SDL_Log(ex.what());
    }catch(...){
        SDL_Log("Error Occured\n");
    }

    return 0;

}