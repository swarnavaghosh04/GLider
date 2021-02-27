#include "HermyGL/Window.hpp"

namespace hgl{
/*
    Window::Window(const char* title, int width, int height, Uint32 windowFlags, Uint32 rendererFlags){

        window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width, height,
            windowFlags | SDL_WINDOW_OPENGL);

        if(window == NULL)
            throw std::runtime_error(SDL_GetError());

        renderer = SDL_CreateRenderer(window, -1, rendererFlags);

        if(renderer == NULL){
            SDL_DestroyWindow(window);
            throw std::runtime_error(SDL_GetError());
        }
        
        glContext = SDL_GL_CreateContext(window);

        if(glContext == NULL){
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            throw std::runtime_error(SDL_GetError());
        }

        if(SDL_GL_SetSwapInterval(0) != 0){
            SDL_GL_DeleteContext(glContext);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            throw std::runtime_error(SDL_GetError());
        }

        if(!gladLoadGL()) {
            SDL_GL_DeleteContext(glContext);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            throw std::runtime_error("GLAD Unable to load OpenGL");
        }

        enable(Multisample);
        enable(DepthTest);

    }

    Window::~Window(){

        SDL_GL_DeleteContext(glContext);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return;
        
    }
*/
    Window::Window(const char* title, int width, int height, unsigned int windowFlags):
        window(
            SDL_CreateWindow(
                title,
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                width, height,
                windowFlags | SDL_WINDOW_OPENGL
            )
        )
    {

        // window = SDL_CreateWindow(
        //     title,
        //     SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        //     width, height,
        //     windowFlags | SDL_WINDOW_OPENGL);

        if(window == NULL)
            throw std::runtime_error(SDL_GetError());
        
    }

    Window::~Window(){
        SDL_DestroyWindow(window);
    }

    Window::Window(Window&& other):
        window(other.window)
    {
        other.window = nullptr;
    }

    Window& Window::operator=(Window&& other){
        std::swap(window, other.window);
        return *this;
    }

    Renderer::Renderer(const Window& window, unsigned int rendererFlags):
        renderer(
            SDL_CreateRenderer(window(), -1, rendererFlags)
        )
    {

        // renderer = SDL_CreateRenderer(window(), -1, rendererFlags);
        
        if(renderer == NULL)
            throw std::runtime_error(SDL_GetError());

    }

    Renderer::~Renderer(){
        SDL_DestroyRenderer(renderer);
    }

    Renderer::Renderer(Renderer&& other):
        renderer(other.renderer)
    {
        other.renderer = nullptr;
    }

    Renderer& Renderer::operator=(Renderer&& other){
        std::swap(renderer, other.renderer);
        return *this;
    }

    OpenGLContext::OpenGLContext(const Window& window):
        glContext( SDL_GL_CreateContext(window()) )
    {

        //glContext = SDL_GL_CreateContext(window());
        
        if(glContext == NULL)
            throw std::runtime_error(SDL_GetError());

    }

    OpenGLContext::~OpenGLContext(){
        SDL_GL_DeleteContext(glContext);
    }

    OpenGLContext::OpenGLContext(OpenGLContext&& other):
        glContext(other.glContext)
    {
        other.glContext = NULL;
    }

    OpenGLContext& OpenGLContext::operator=(OpenGLContext&& other){
        std::swap(glContext, other.glContext);
        return *this;
    }

    OpenGLWindow::OpenGLWindow(const char* title, int width, int height, unsigned int windowFlags, unsigned int rendererFlags):
        window{title, width, height, windowFlags},
        renderer{window, rendererFlags},
        glContext{window}
    {
        if(!gladLoadGL())
            throw std::runtime_error("GLAD Unable to load OpenGL");

        enable(Multisample);
        enable(DepthTest);
    }

}