#include "HermyGL/HermyGL.hpp"

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

int main(int argc, const char** argv){

    try{
        hgl::initialize(3,0);
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

        hgl::OpenGLWindow win{"Triangle", int(float(dm.w)*3.f/4.f), int(float(dm.h)*3.f/4.f)};

        hgl::VertexArray va;
        hgl::Buffer<hgl::VertexBuffer> vb;
        hgl::Shaders shaders;

        vb.feedData(vertecies, hgl::UseDynamicDraw);
        va.readBufferData<float>(
            vb,
            std::array<hgl::LayoutElement, 2>{
                hgl::LayoutElement{hgl::D2, hgl::Norm_FALSE},   // Position
                hgl::LayoutElement{hgl::D3, hgl::Norm_FALSE}    // Color
            }
        );

        shaders.compileString(hgl::VertexShader, vertexShader);
        shaders.compileString(hgl::FragmentShader, fragmentShader);
        shaders.link();
        shaders.validate();

        va.bind();
        shaders.bind();

        bool keepRunning = true;
        SDL_Event e;

        while(keepRunning){

            hgl::clear(hgl::ColorBufferBit);
            
            va.draw(hgl::DrawTriangles, 0, 3);

            SDL_GL_SwapWindow(win.get());
            
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
        SDL_Log(e.what());
    }

    hgl::quit();

}