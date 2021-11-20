#include "util.hpp"

SDL::Window::Window(const char* title, int width, int height, unsigned int windowFlags):
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
    PRINT_DEBUG("Window Created\n");
}

SDL::Window::~Window() noexcept {
    SDL_DestroyWindow(window);
    PRINT_DEBUG("Window Destroyed\n");
}

SDL::Window::Window(SDL::Window&& other) noexcept:
    window(other.window)
{
    other.window = nullptr;
    PRINT_DEBUG("Window Move Contructed\n");
}

SDL::Window& SDL::Window::operator=(SDL::Window&& other) noexcept{
    std::swap(window, other.window);
    PRINT_DEBUG("Window Move Assigned\n");
    return *this;
}

SDL::Renderer::Renderer(SDL::Window& window, unsigned int rendererFlags):
    renderer(
        SDL_CreateRenderer(window.get(), -1, rendererFlags)
    )
{
    if(renderer == NULL)
        throw std::runtime_error(SDL_GetError());
    PRINT_DEBUG("Renderer Created\n");
}

SDL::Renderer::~Renderer() noexcept{
    SDL_DestroyRenderer(renderer);
    PRINT_DEBUG("Renderer Destroyed\n");
}

SDL::Renderer::Renderer(Renderer&& other) noexcept:
    renderer(other.renderer)
{
    other.renderer = nullptr;
    PRINT_DEBUG("Renderer Move Contructed\n");
}

SDL::Renderer& SDL::Renderer::operator=(SDL::Renderer&& other) noexcept{
    std::swap(renderer, other.renderer);
    PRINT_DEBUG("Renderer Move Assigned\n");
    return *this;
}

SDL::OpenGLContext::OpenGLContext(SDL::Window& window):
    glContext( SDL_GL_CreateContext( window.get()) )
{   
    if(glContext == NULL)
        throw std::runtime_error(SDL_GetError());
    PRINT_DEBUG("OpenGLContext Created\n");
}

SDL::OpenGLContext::~OpenGLContext() noexcept{
    SDL_GL_DeleteContext(glContext);
    PRINT_DEBUG("OpenGLContext Destroyed\n");
}

SDL::OpenGLContext::OpenGLContext(SDL::OpenGLContext&& other) noexcept:
    glContext(other.glContext)
{
    other.glContext = NULL;
    PRINT_DEBUG("OpenGLContext Move Contructed\n");
}

SDL::OpenGLContext& SDL::OpenGLContext::operator=(SDL::OpenGLContext&& other) noexcept{
    std::swap(glContext, other.glContext);
    PRINT_DEBUG("OpenGLContext Move Assigned\n");
    return *this;
}

SDL::OpenGLWindow::OpenGLWindow(
    const char* title,
    int width, int height,
    unsigned int windowFlags,
    unsigned int rendererFlags)
:
    SDL::Window(title, width, height, windowFlags),
    renderer(*(Window*)(&(this->window)), rendererFlags | SDL_WINDOW_OPENGL),
    glContext(*(Window*)(&(this->window)))
{}

int setAttributesWithVersion(int major, int minor){
    return
          SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE)
        + SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major)
        + SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor)
        + SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1)
        + SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32)
        + SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1)
        + SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4)
        + SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
}

SDL::SDL(int major, int minor){

    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG);

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw std::runtime_error(SDL_GetError());

    int errorVal = setAttributesWithVersion(major, minor);

    if(errorVal < 0){
        SDL_Quit();
        throw std::runtime_error(SDL_GetError());
    }
}

SDL::~SDL() noexcept{
    SDL_Quit();
}