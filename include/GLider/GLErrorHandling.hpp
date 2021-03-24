#ifndef GLI_ERROR_HANDLING__H_
#define GLI_ERROR_HANDLING__H_

#include "GLider/GLider_core.hpp"

namespace gli{

    extern int numErrors;
    void checkErrors() noexcept;

}

#ifdef GLI_DEBUG
#define GL_CALL(x)\
    x;\
    gli::checkErrors();\
    if(gli::numErrors!=0){\
        SDL_LogError(\
            SDL_LOG_CATEGORY_APPLICATION,\
            "    (%u) %s:%i:%s()\n",\
            gli::numErrors--,\
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
