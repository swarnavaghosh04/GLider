#ifndef HERMYGL__H_
#define HERMYGL__H_

#include "HermyGL/HermyGL_export.h"
#include "glad/glad.h"
#include "SDL2/SDL.h"

namespace hgl{

    class HERMYGL_EXPORT Window{

    private:
        SDL_Window *window;
        
    public:
        Window(const char* title, int width, int height, Uint32 windowFlags, Uint32 rendererFlags);

    };

}

#endif