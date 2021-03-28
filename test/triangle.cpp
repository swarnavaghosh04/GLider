#include "GLider/GLider.hpp"

const char* vertexShader = R"CODE(
    #version 330 core

    layout(location = 0) in vec4 vertexPos;
    layout(location = 1) in vec3 vertexColor;

    out vec3 fragmentColor;

    void main(){
        gl_Position = vertexPos;
        fragmentColor = vertexColor;
    }

)CODE";

const char* fragmentShader = R"CODE(
    #version 330 core

    in vec3 fragmentColor;

    void main(){
        gl_FragColor = vec4(fragmentColor, 1.f);
    }

)CODE";

int main(){

    try{
        gli::initialize(3,0);
    }catch(std::exception& e){
        SDL_Log("cannot initialize: %s", e.what());
        return 1;
    }

    try{

        std::array<float, 5*3> vertecies = {
        //---Positions---||-----Colors-----||
            -.75, -.75,     1.f, 0.f, 0.f,
               0,  .75,     0.f, 1.f, 0.f,
             .75, -.75,     0.f, 0.f, 1.f
        };

        SDL_DisplayMode dm;
        if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
            throw std::runtime_error(SDL_GetError());

        gli::OpenGLWindow win{"Triangle", int(float(dm.w)*3.f/4.f), int(float(dm.h)*3.f/4.f)};

        gli::VertexArray va;
        gli::Buffer<gli::VertexBuffer> vb;
        gli::Shaders shaders;

        vb.feedData(vertecies, gli::UseDynamicDraw);
        va.readBufferData<float>(
            vb,
            std::array<gli::LayoutElement, 2>{
                gli::LayoutElement{gli::D2, gli::Norm_FALSE},   // Position
                gli::LayoutElement{gli::D3, gli::Norm_FALSE}    // Color
            }
        );

        shaders.compileString(gli::VertexShader, vertexShader);     // shaders.compileFile() can also be used if you
        shaders.compileString(gli::FragmentShader, fragmentShader); // wrote your shader source in a separate file
        shaders.link();
        shaders.validate();

        va.bind();
        shaders.bind();

        bool keepRunning = true;
        SDL_Event e;

        while(keepRunning){

            gli::clear(gli::ColorBufferBit | gli::DepthBufferBit);
            
            va.draw(gli::DrawTriangles, 0, 3);

            // SDL_GL_SwapWindow(win.get());
            win.swap();
            
            while(SDL_PollEvent(&e)){

                switch(e.type){
                case SDL_QUIT:
                    keepRunning = false;
                    break;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                    case SDLK_ESCAPE:
                        if(e.key.keysym.mod & KMOD_SHIFT)
                            keepRunning = false;
                        break;
                    }
                    break;
                }

            }

        }

    }catch(std::exception& e){
        SDL_Log("Error Occured: %s\n", typeid(e).name());
        SDL_Log("%s", e.what());
    }

    gli::quit();

}