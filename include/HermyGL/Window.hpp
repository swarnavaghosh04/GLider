#ifndef HGL_WINDOW__H_
#define HGL_WINDOW__H_

#include "HermyGL/HermyGL_core.hpp"
#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    class HERMYGL_EXPORT Window{
    private:
        SDL_Window *window;
    public:
        Window(const char* title, int width, int height, unsigned int windowFlags = 0);
        ~Window();
        Window(const Window&) = delete;
        Window(Window&& other);
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&& other);
        SDL_Window* operator()() const { return window; }
    };

    class HERMYGL_EXPORT Renderer{
    private:
        SDL_Renderer *renderer;
    public:
        Renderer(const Window& window, unsigned int rendererFlags = 0);
        ~Renderer();
        Renderer(const Renderer&) = delete;
        Renderer(Renderer&& other);
        Renderer& operator=(const Renderer&) = delete;
        Renderer& operator=(Renderer&& other);
        SDL_Renderer* operator()() const {return renderer;}
    };

    class HERMYGL_EXPORT OpenGLContext{
    private:
        SDL_GLContext glContext;
    public:
        OpenGLContext(const Window& window);
        ~OpenGLContext();
        OpenGLContext(const OpenGLContext&) = delete;
        OpenGLContext(OpenGLContext&& other);
        OpenGLContext& operator=(const OpenGLContext&) = delete;
        OpenGLContext& operator=(OpenGLContext&& other);
        SDL_GLContext operator()() const {return glContext;}
    };

    class HERMYGL_EXPORT OpenGLWindow{
    private:
        Window window;
        Renderer renderer;
        OpenGLContext glContext;
    public:
        OpenGLWindow(const char* title, int width, int height, unsigned int windowFlags = 0, unsigned int rendererFlags = 0);
        // OpenGLWindow(const OpenGLWindow&) = delete;
        // OpenGLWindow(OpenGLWindow&& other);
        // OpenGLWindow& operator=(const OpenGLWindow&) = delete;
        // OpenGLWindow& operator=(OpenGLWindow&& other);
        SDL_Window* operator()() const { return window(); }
    };
    
}

#endif