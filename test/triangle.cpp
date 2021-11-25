
#include <cstdio>
#include <cstdlib>
#include <chrono>

#include "GLider/GLider.hpp"
#include "util.hpp"

//! [Shader Sources]

const char* vertexShader = R"CODE(

    #version 140

    in vec4 vertexPos;
    in vec3 vertexColor;

    out vec3 fragmentColor;

    void main(){
        gl_Position = vertexPos;
        fragmentColor = vertexColor;
    }

)CODE";

const char* fragmentShader = R"CODE(
    #version 140

    in vec3 fragmentColor;

    void main(){
        gl_FragColor = vec4(fragmentColor, 1.f);
    }

)CODE";

//! [Shader Sources]

int main(int argc, char* argv[]){

	// if no arguments are passed, keep window open until terminated
	// If valid float has been passed, keep window open for that many milliseconds

    float openDuration_ms = 0.f;
    auto start = std::chrono::steady_clock::now();

    if(argc >= 2) openDuration_ms = std::atof(argv[1]);

    try{

        SDL sdl(3,0);

        SDL_DisplayMode dm;
        if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
            throw std::runtime_error(SDL_GetError());

        SDL::OpenGLWindow win{"Triangle", (dm.w*3)/4, (dm.h*3)/4};

        //! [GLider Init]
        gli::initialize(SDL_GL_GetProcAddress);
        //! [GLider Init]

        //! [GLider Variable Declarations]
        gli::VertexArray va;
        gli::Buffer<gli::VertexBuffer> vb;
        gli::ShaderProgram shaders;
        //! [GLider Variable Declarations]

        //! [Vertices]
        std::array<float, 5*3> vertecies = {
        //---Positions---||-----Colors-----||
            -.75, -.75,     1.f, 0.f, 0.f,
               0,  .75,     0.f, 1.f, 0.f,
             .75, -.75,     0.f, 0.f, 1.f
        };
        //! [Vertices]

        //! [Store Data in VRAM]
        vb.feedData(vertecies, gli::UseDynamicDraw);
        {
            gli::Layout layout;
            layout.push<float>(gli::D2, false);
            layout.push<float>(gli::D3, false);
            va.readBufferData(
                vb,
                layout
            );
        }
        //! [Store Data in VRAM]

        //! [Vertex Attribute Locations]
        shaders.bindAttribLocation(0, "vertexPos");
        shaders.bindAttribLocation(1, "vertexColor");
        //! [Vertex Attribute Locations]

        //! [Shader Compilation]
        shaders.compileString(gli::VertexShader, vertexShader);     // shaders.compileFile() can also be used if you
        shaders.compileString(gli::FragmentShader, fragmentShader); // wrote your shader source in a separate file
        shaders.link();
        shaders.validate();
        //! [Shader Compilation]

        //! [Ensure Bind]
        va.bind();
        shaders.bind();
        //! [Ensure Bind]

        bool keepRunning = true;
        SDL_Event e;

        while(keepRunning){
            
            //! [Draw]
            gli::clear(gli::ColorBufferBit | gli::DepthBufferBit);
            va.draw(gli::DrawTriangles, 0, 3);
            //! [Draw]
            
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

            if(openDuration_ms > 0.f){
            	if(
            		std::chrono::duration_cast<std::chrono::duration<float, std::milli>>
            		(std::chrono::steady_clock::now() - start).count() >= openDuration_ms
            	)
            		keepRunning = false;
            }

        }

    }catch(std::exception& e){
        std::printf("Error Occured: %s\n", typeid(e).name());
        std::printf("%s", e.what());
    }

    return 0;

}