
#include "GLider/GLider.hpp"
#include <cstdio>
#include <cstdlib>
#include <chrono>

const char* vertexShader = R"CODE(

    #version 140
    #extension GL_ARB_separate_shader_objects : require
    
    layout(location = 0) in vec4 vertexPos;
    layout(location = 1) in vec3 vertexColor;

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

int main(int argc, char* argv[]){

	// if not arguments are passed, keep window open until terminated
	// If valid float has been passed, keep window open for that many milliseconds

    float openDuration_ms = 0.f;
    auto start = std::chrono::steady_clock::now();

    if(argc >= 2) openDuration_ms = std::atof(argv[1]);

    try{
        gli::initialize(3,1);
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
        
        std::printf("OpenGL GLAD verision   : %d.%d\n", GLVersion.major, GLVersion.minor);
        std::printf("OpenGL Version         : %s \n", glGetString(GL_VERSION));
        std::printf("OpenGL Shading Version : %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
        std::printf("OpenGL Vendor          : %s \n", glGetString(GL_VENDOR));
        std::printf("OpenGL Renderer        : %s \n", glGetString(GL_RENDERER));

        gli::VertexArray va;
        gli::Buffer<gli::VertexBuffer> vb;
        gli::ShaderProgram shaders;

        // shaders.bindAttribLocation(0, "vertexPos");
        // shaders.bindAttribLocation(1, "vertexColor");

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

    gli::quit();
    return 0;

}