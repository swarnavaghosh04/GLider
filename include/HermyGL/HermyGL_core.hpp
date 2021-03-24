#ifndef HGL_CORE__H_
#define HGL_CORE__H_

#ifdef HGL_DEBUG
    /*
    This needs priority of SDL_LOG_CATEGORY_APPLICATION to be set to
    SDL_LOG_PRIORITY_DEBUG Which is done in hgl::initialize() which
    is decalred in HermyGL.hpp
    */
    #define HGL_PRINT_DEBUG(format, ...)\
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, format, ##__VA_ARGS__);
#else
    #define HGL_PRINT_DEBUG(format, ...)
#endif

#include <SDL2/SDL.h>
#include <stdexcept>
#include "glad/glad.h"

#endif