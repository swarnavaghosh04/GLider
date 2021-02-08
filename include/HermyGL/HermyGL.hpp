#ifndef HERMYGL__H_
#define HERMYGL__H_

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include "HermyGL/HermyGL_core.hpp"
#include "HermyGL/Window.hpp"

namespace hgl{

    HERMYGL_EXPORT error initialize();
    HERMYGL_EXPORT void quit();

}

#endif