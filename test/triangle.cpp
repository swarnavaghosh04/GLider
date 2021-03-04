#include "HermyGL/HermyGL.hpp"

const char* vertexShader = R"CODE(
    #version 330 core

    layout(location = 0) in vec4 pos;

    void main(){
        gl_Position = pos;
    }

)CODE";

const char* fragmentShader = R"CODE(
    #version 330 core

    void main(){
        gl_FragColor = vec4(0.f, 1.f, 0.f, 1.f);
    }

)CODE";

int main(int argc, const char** argv){

    try{
        hgl::initialize();
    }catch(std::exception& e){
        SDL_Log("cannot initialize: %s", e.what());
    }

    try{

        std::array<float, 2*3> vertecies = {
            -.5, -.5,
            0,  .5,
            .5, -.5
        };

        SDL_DisplayMode dm;
        if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
            SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
            return 1;
        }
        
        SDL_Log("window: %d x %d [%dHz]\n", dm.w, dm.h, dm.refresh_rate);

        hgl::OpenGLWindow win{"Triangle", 400, 800, /*SDL_WINDOW_FULLSCREEN_DESKTOP*/};

        if (SDL_GetCurrentDisplayMode(0, &dm) != 0) {
            SDL_Log("SDL_GetCurrentDisplayMode failed: %s", SDL_GetError());
            return 1;
        }

        SDL_Log("window: %d x %d [%dHz]\n", dm.w, dm.h, dm.refresh_rate);

        hgl::VertexArray va;
        hgl::Buffer<hgl::VertexBuffer> vb;
        hgl::Shaders shaders;

        vb.feedData(vertecies, hgl::UseStaticDraw);
        va.readBufferData<float>(vb, std::array<hgl::LayoutElement, 1>({hgl::D2, hgl::Norm_FALSE}));

        shaders.compileString(hgl::VertexShader, vertexShader);
        shaders.compileString(hgl::FragmentShader, fragmentShader);
        shaders.link();
        shaders.validate();
        shaders.use();

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