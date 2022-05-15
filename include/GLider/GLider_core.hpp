#ifndef GLI_CORE__H_
#define GLI_CORE__H_

#include <stdexcept>
#include "glad/glad.h"

#ifndef GLI_DEBUG
#define GLI_DEBUG 0
#endif

#if GLI_DEBUG & !defined(GLAD_DEBUG)
#error\
    "GLI_DEBUG is on but GLAD_DEBUG is not defined! "\
    "Please make sure GLAD is using c-debug as generator"
#endif

#endif