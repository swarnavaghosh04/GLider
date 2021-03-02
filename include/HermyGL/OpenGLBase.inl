#ifndef HGL_OPENGL_BASE__I_
#define HGL_OPENGL_BASE__I_

#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    inline BufferBit operator|(BufferBit a, BufferBit b){
        return static_cast<BufferBit>(
            static_cast<unsigned int>(a) | static_cast<unsigned int>(b)
        );
    }

    inline void clear(BufferBit mask) noexcept{
        GL_CALL(glClear(mask | BufferBit::DepthBufferBit));
    }

    inline void enable(Capability_NI cap) noexcept{
        GL_CALL(glEnable(cap));
    }

    inline void enable(Capability_I cap) noexcept{
        GL_CALL(glEnable(cap));
    }

    inline void enable(Capability_I cap, unsigned int index) noexcept{
        GL_CALL(glEnablei(cap, index));
    }

    inline void disable(Capability_NI cap) noexcept{
        GL_CALL(glDisable(cap));
    }

    inline void disable(Capability_I cap) noexcept{
        GL_CALL(glDisable(cap));
    }

    inline void disable(Capability_I cap, unsigned int index) noexcept{
        GL_CALL(glDisablei(cap, index));
    }

}

#endif