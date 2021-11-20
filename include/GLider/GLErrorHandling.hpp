#ifndef GLI_ERROR_HANDLING__H_
#define GLI_ERROR_HANDLING__H_

#include <cstdio>
#include "GLider/GLider_core.hpp"

namespace gli{
    
    extern int numErrors; ///< @private
    void checkErrors() noexcept; ///< @private

}

#ifdef GLI_DEBUG
/// @private
#define GL_CALL(x)\
    x;\
    gli::checkErrors();\
    while(gli::numErrors!=0){\
        std::printf(\
            "    (%u) %s:%i:%s()\n",\
            gli::numErrors--,\
            __FILE__,\
            __LINE__,\
            __FUNCTION__);\
        std::printf(\
            "    %s\n",\
            #x);\
    }
#else
/// @private
#define GL_CALL(x) x
#endif

// use: SDL_LOG_CATEGORIE_APPLICATION

#endif
