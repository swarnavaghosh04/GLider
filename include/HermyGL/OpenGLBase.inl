#ifndef HGL_OPENGL_BASE__I_
#define HGL_OPENGL_BASE__I_

#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    inline void clear(unsigned int mask){
        GL_CALL(glClear(mask | GL_DEPTH_BUFFER_BIT));
    }

    inline const unsigned int RuntimeOpenGLBase::getId() const
    { return id; }

}

#endif