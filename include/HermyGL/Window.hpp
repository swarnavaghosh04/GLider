#ifndef HGL_WINDOW__H_
#define HGL_WINDOW__H_

#include "HermyGL/HermyGL_core.hpp"

namespace hgl{

    class HERMYGL_EXPORT Window{

    private:

        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_GLContext glContext;
        
    public:

        Window(const char* title, int width, int height, Uint32 windowFlags = 0, Uint32 rendererFlags = 0);
        ~Window();

        SDL_Window* getWindow() const { return window; }
    };
    
}

#endif