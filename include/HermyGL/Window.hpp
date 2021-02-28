#ifndef HGL_WINDOW__H_
#define HGL_WINDOW__H_

#include "HermyGL/HermyGL_core.hpp"
#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    class HERMYGL_EXPORT Window{
    protected:
        SDL_Window *window;
    public:
        Window(const char* title, int width, int height, unsigned int windowFlags = 0);
        ~Window() noexcept(true);
        Window(const Window&) = delete;
        Window(Window&& other) noexcept(true);
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&& other) noexcept(true);
        const SDL_Window* get() const noexcept(true) { return window; }
        SDL_Window* get() noexcept(true) { return window; }
    };

    class HERMYGL_EXPORT Renderer{
    protected:
        SDL_Renderer *renderer;
    public:
        Renderer(Window& window, unsigned int rendererFlags = 0);
        ~Renderer() noexcept(true);
        Renderer(const Renderer&) = delete;
        Renderer(Renderer&& other) noexcept(true);
        Renderer& operator=(const Renderer&) = delete;
        Renderer& operator=(Renderer&& other) noexcept(true);
        const SDL_Renderer* get() const noexcept(true) {return renderer;}
        SDL_Renderer* get() noexcept(true) {return renderer;}
    };

    class HERMYGL_EXPORT OpenGLContext{
    protected:
        SDL_GLContext glContext;
    public:
        OpenGLContext(Window& window);
        ~OpenGLContext() noexcept(true);
        OpenGLContext(const OpenGLContext&) = delete;
        OpenGLContext(OpenGLContext&& other) noexcept(true);
        OpenGLContext& operator=(const OpenGLContext&) = delete;
        OpenGLContext& operator=(OpenGLContext&& other) noexcept(true);
        const SDL_GLContext& get() const noexcept(true) {return glContext;}
        SDL_GLContext& get() noexcept(true) {return glContext;}
    };

    class HERMYGL_EXPORT OpenGLWindow : public Window{
    protected:
        Renderer renderer;
        OpenGLContext glContext;
    public:
        OpenGLWindow(
            const char* title,
            int width, int height,
            unsigned int windowFlags = 0,
            unsigned int rendererFlags = 0);
    };
    
}

#endif