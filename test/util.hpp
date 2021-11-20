#ifndef UTIL__H
#define UTIL__H

#define SDL_MAIN_HANDLED

#include <stdexcept>
#include <SDL2/SDL.h>

#define PRINT_DEBUG(format, ...)\
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, format, ##__VA_ARGS__);

class SDL{
public:

    class Window{
    protected:
        SDL_Window *window;
    public:
        Window(const char* title, int width, int height, unsigned int windowFlags = 0);
        ~Window() noexcept;
        Window(const Window&) = delete;
        Window(Window&& other) noexcept;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&& other) noexcept;
        const SDL_Window* get() const noexcept { return window; }
        SDL_Window* get() noexcept { return window; }
    };

    class Renderer{
    protected:
        SDL_Renderer *renderer;
    public:
        Renderer(Window& window, unsigned int rendererFlags = 0);
        ~Renderer() noexcept;
        Renderer(const Renderer&) = delete;
        Renderer(Renderer&& other) noexcept;
        Renderer& operator=(const Renderer&) = delete;
        Renderer& operator=(Renderer&& other) noexcept;
        const SDL_Renderer* get() const noexcept {return renderer;}
        SDL_Renderer* get() noexcept {return renderer;}
    };

    class OpenGLContext{
    protected:
        SDL_GLContext glContext;
    public:
        OpenGLContext(Window& window);
        ~OpenGLContext() noexcept;
        OpenGLContext(const OpenGLContext&) = delete;
        OpenGLContext(OpenGLContext&& other) noexcept;
        OpenGLContext& operator=(const OpenGLContext&) = delete;
        OpenGLContext& operator=(OpenGLContext&& other) noexcept;
        const SDL_GLContext& get() const noexcept {return glContext;}
        SDL_GLContext& get() noexcept {return glContext;}
    };

    class OpenGLWindow : Window{
        protected:
        Renderer renderer;
        OpenGLContext glContext;
    public:
        OpenGLWindow(
            const char* title,
            int width, int height,
            unsigned int windowFlags = 0,
            unsigned int rendererFlags = 0);
        void swap() noexcept { SDL_GL_SwapWindow(this->window); }
    };

    SDL(int major, int minor);
    ~SDL() noexcept;
};

#endif