#ifndef HGL_ERROR_HANDLING__H_
#define HGL_ERROR_HANDLING__H_

#include "HermyGL/HermyGL_core.hpp"

namespace hgl{

    extern int numErrors;
    void checkErrors() noexcept;

}

#ifdef HGL_DEBUG
#define GL_CALL(x)\
    x;\
    hgl::checkErrors();\
    if(hgl::numErrors!=0){\
        SDL_LogError(\
            SDL_LOG_CATEGORY_APPLICATION,\
            "    (%u) %s:%i:%s()\n",\
            hgl::numErrors--,\
            __FILE__,\
            __LINE__,\
            __FUNCTION__);\
        SDL_LogError(\
            SDL_LOG_CATEGORY_APPLICATION,\
            "    %s\n",\
            #x);\
    }
#else
#define GL_CALL(x) x
#endif

#endif
