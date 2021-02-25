#ifndef HGL_OPENGL_BASE__I_
#define HGL_OPENGL_BASE__I_

#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    inline void clear(BufferBit mask){
        GL_CALL(glClear(mask | BufferBit::DepthBufferBit));
    }

    inline void enable(Capability cap){
        GL_CALL(glEnable(cap));
    }

    inline void disable(Capability cap){
        GL_CALL(glDisable(cap));
    }

    inline const unsigned int OpenGLBase::getId() const
    { return id; }

}

#endif