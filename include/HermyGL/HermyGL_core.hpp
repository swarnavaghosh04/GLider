#ifndef HGL_CORE__H_
#define HGL_CORE__H_

#include <SDL2/SDL.h>
#include "glad/glad.h"
#include "HermyGL/HermyGL_export.h"

namespace hgl{

    struct error{
        int code;
        const char* message;
    };

    HERMYGL_EXPORT extern const char* const noError;

}

#endif