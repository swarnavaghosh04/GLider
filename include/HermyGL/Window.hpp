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
        ~Window();
        Window(const Window&) = delete;
        Window(Window&& other);
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&& other);
        const SDL_Window* operator()() const { return window; }
        SDL_Window* operator()() { return window; }
    };

    class HERMYGL_EXPORT Renderer{
    protected:
        SDL_Renderer *renderer;
    public:
        Renderer(Window& window, unsigned int rendererFlags = 0);
        ~Renderer();
        Renderer(const Renderer&) = delete;
        Renderer(Renderer&& other);
        Renderer& operator=(const Renderer&) = delete;
        Renderer& operator=(Renderer&& other);
        const SDL_Renderer* operator()() const {return renderer;}
        SDL_Renderer* operator()() {return renderer;}
    };

    class HERMYGL_EXPORT OpenGLContext{
    protected:
        SDL_GLContext glContext;
    public:
        OpenGLContext(Window& window);
        ~OpenGLContext();
        OpenGLContext(const OpenGLContext&) = delete;
        OpenGLContext(OpenGLContext&& other);
        OpenGLContext& operator=(const OpenGLContext&) = delete;
        OpenGLContext& operator=(OpenGLContext&& other);
        const SDL_GLContext& operator()() const {return glContext;}
        SDL_GLContext& operator()() {return glContext;}
    };

    class HERMYGL_EXPORT OpenGLWindow : public Window{
    protected:
        Renderer renderer;
        OpenGLContext glContext;
    public:
        OpenGLWindow(const char* title, int width, int height, unsigned int windowFlags = 0, unsigned int rendererFlags = 0);
    };
    
}

#endif