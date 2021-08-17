#ifndef GLI_CORE__H_
#define GLI_CORE__H_

#ifdef GLI_DEBUG
    /*
    This needs priority of SDL_LOG_CATEGORY_APPLICATION to be set to
    SDL_LOG_PRIORITY_DEBUG Which is done in gli::initialize() which
    is decalred in GLider.hpp
    */
    #define GLI_PRINT_DEBUG(format, ...)\
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, format, ##__VA_ARGS__);
#else
    #define GLI_PRINT_DEBUG(format, ...)
#endif

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <stdexcept>
#include "glad/glad.h"

#endif