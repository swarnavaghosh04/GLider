#include "HermyGL/Window.hpp"

namespace hgl{

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
        if(window == NULL)
            throw std::runtime_error(SDL_GetError());
        #ifdef HGL_DEBUG
        SDL_Log("Window Created\n");
        #endif
    }

    Window::~Window() noexcept(true) {
        SDL_DestroyWindow(window);
        #ifdef HGL_DEBUG
        SDL_Log("Window Destroyed\n");
        #endif
    }

    Window::Window(Window&& other) noexcept(true):
        window(other.window)
    {
        other.window = nullptr;
        #ifdef HGL_DEBUG
        SDL_Log("Window Move Contructed\n");
        #endif
    }

    Window& Window::operator=(Window&& other) noexcept(true){
        std::swap(window, other.window);
        #ifdef HGL_DEBUG
        SDL_Log("Window Move Assigned\n");
        #endif
        return *this;
    }

    Renderer::Renderer(Window& window, unsigned int rendererFlags):
        renderer(
            SDL_CreateRenderer(window.get(), -1, rendererFlags)
        )
    {
        if(renderer == NULL)
            throw std::runtime_error(SDL_GetError());
        #ifdef HGL_DEBUG
        SDL_Log("Renderer Created\n");
        #endif
    }

    Renderer::~Renderer() noexcept(true){
        SDL_DestroyRenderer(renderer);
        #ifdef HGL_DEBUG
        SDL_Log("Renderer Destroyed\n");
        #endif
    }

    Renderer::Renderer(Renderer&& other) noexcept(true):
        renderer(other.renderer)
    {
        other.renderer = nullptr;
        #ifdef HGL_DEBUG
        SDL_Log("Renderer Move Contructed\n");
        #endif
    }

    Renderer& Renderer::operator=(Renderer&& other) noexcept(true){
        std::swap(renderer, other.renderer);
        #ifdef HGL_DEBUG
        SDL_Log("Renderer Move Assigned\n");
        #endif
        return *this;
    }

    OpenGLContext::OpenGLContext(Window& window):
        glContext( SDL_GL_CreateContext( window.get()) )
    {   
        if(glContext == NULL)
            throw std::runtime_error(SDL_GetError());
        #ifdef HGL_DEBUG
        SDL_Log("OpenGLContext Created\n");
        #endif
    }

    OpenGLContext::~OpenGLContext() noexcept(true){
        SDL_GL_DeleteContext(glContext);
        #ifdef HGL_DEBUG
        SDL_Log("OpenGLContext Destroyed\n");
        #endif
    }

    OpenGLContext::OpenGLContext(OpenGLContext&& other) noexcept(true):
        glContext(other.glContext)
    {
        other.glContext = NULL;
        #ifdef HGL_DEBUG
        SDL_Log("OpenGLContext Move Contructed\n");
        #endif
    }

    OpenGLContext& OpenGLContext::operator=(OpenGLContext&& other) noexcept(true){
        std::swap(glContext, other.glContext);
        #ifdef HGL_DEBUG
        SDL_Log("OpenGLContext Move Assigned\n");
        #endif
        return *this;
    }

    OpenGLWindow::OpenGLWindow(
        const char* title,
        int width, int height,
        unsigned int windowFlags,
        unsigned int rendererFlags)
    :
        Window{title, width, height, windowFlags},
        renderer{*(Window*)(&(this->window)), rendererFlags},
        glContext{*(Window*)(&(this->window))}
    {
        if(!gladLoadGL())
            throw std::runtime_error("GLAD Unable to load OpenGL");

        enable(Multisample);
        enable(DepthTest);
    }

}