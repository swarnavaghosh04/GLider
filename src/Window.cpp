#include "GLider/Window.hpp"

namespace gli{

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
        GLI_PRINT_DEBUG("Window Created\n");
    }

    Window::~Window() noexcept {
        SDL_DestroyWindow(window);
        GLI_PRINT_DEBUG("Window Destroyed\n");
    }

    Window::Window(Window&& other) noexcept:
        window(other.window)
    {
        other.window = nullptr;
        GLI_PRINT_DEBUG("Window Move Contructed\n");
    }

    Window& Window::operator=(Window&& other) noexcept{
        std::swap(window, other.window);
        GLI_PRINT_DEBUG("Window Move Assigned\n");
        return *this;
    }

    Renderer::Renderer(Window& window, unsigned int rendererFlags):
        renderer(
            SDL_CreateRenderer(window.get(), -1, rendererFlags)
        )
    {
        if(renderer == NULL)
            throw std::runtime_error(SDL_GetError());
        GLI_PRINT_DEBUG("Renderer Created\n");
    }

    Renderer::~Renderer() noexcept{
        SDL_DestroyRenderer(renderer);
        GLI_PRINT_DEBUG("Renderer Destroyed\n");
    }

    Renderer::Renderer(Renderer&& other) noexcept:
        renderer(other.renderer)
    {
        other.renderer = nullptr;
        GLI_PRINT_DEBUG("Renderer Move Contructed\n");
    }

    Renderer& Renderer::operator=(Renderer&& other) noexcept{
        std::swap(renderer, other.renderer);
        GLI_PRINT_DEBUG("Renderer Move Assigned\n");
        return *this;
    }

    OpenGLContext::OpenGLContext(Window& window):
        glContext( SDL_GL_CreateContext( window.get()) )
    {   
        if(glContext == NULL)
            throw std::runtime_error(SDL_GetError());
        GLI_PRINT_DEBUG("OpenGLContext Created\n");
    }

    OpenGLContext::~OpenGLContext() noexcept{
        SDL_GL_DeleteContext(glContext);
        GLI_PRINT_DEBUG("OpenGLContext Destroyed\n");
    }

    OpenGLContext::OpenGLContext(OpenGLContext&& other) noexcept:
        glContext(other.glContext)
    {
        other.glContext = NULL;
        GLI_PRINT_DEBUG("OpenGLContext Move Contructed\n");
    }

    OpenGLContext& OpenGLContext::operator=(OpenGLContext&& other) noexcept{
        std::swap(glContext, other.glContext);
        GLI_PRINT_DEBUG("OpenGLContext Move Assigned\n");
        return *this;
    }

    OpenGLWindow::OpenGLWindow(
        const char* title,
        int width, int height,
        unsigned int windowFlags,
        unsigned int rendererFlags)
    :
        Window{title, width, height, windowFlags},
        renderer{*(Window*)(&(this->window)), rendererFlags | SDL_WINDOW_OPENGL},
        glContext{*(Window*)(&(this->window))}
    {
        if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
            throw std::runtime_error("GLAD Unable to load OpenGL");

        enable(Multisample);
        enable(DepthTest);
    }

}