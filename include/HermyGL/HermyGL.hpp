#ifndef HERMYGL__H_
#define HERMYGL__H_

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include "glad/glad.h"
#include <SDL2/SDL.h>
#include "HermyGL/HermyGL_export.h"

HERMYGL_EXPORT extern const char* const hglNoError;

namespace hgl{

    struct error{
        int code;
        const char* message;
    };

    HERMYGL_EXPORT extern const char* const noError;

    //HERMYGL_EXPORT extern void (*delay)(Uint32 ms);

    HERMYGL_EXPORT error initialize();
    HERMYGL_EXPORT void quit();

    class HERMYGL_EXPORT Window{

    private:

        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_GLContext glContext;
        
    public:

        Window(error &ret, const char* title, int width, int height, Uint32 windowFlags, Uint32 rendererFlags);
        ~Window();

        inline const SDL_Window* getWindow() const {return window;}
    };

}

#endif