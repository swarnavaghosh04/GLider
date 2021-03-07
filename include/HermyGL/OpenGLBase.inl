#ifndef HGL_OPENGL_BASE__I_
#define HGL_OPENGL_BASE__I_

#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    inline BufferBit operator|(BufferBit a, BufferBit b){
        return static_cast<BufferBit>(
            static_cast<unsigned int>(a) | static_cast<unsigned int>(b)
        );
    }

    template<class Derived>
    OpenGLBase<Derived>::OpenGLBase(OpenGLBase<Derived>&& other) noexcept
        : id(other.id)
    {
        other.id = 0;
    }

    template<class Derived>
    OpenGLBase<Derived>& OpenGLBase<Derived>::operator= (OpenGLBase<Derived>&& other) noexcept{
        std::swap(id, other.id);
        return *this;
    }
    
    template<class Derived>
    inline void OpenGLBase<Derived>::bind() const noexcept{
        ((Derived*)(this))->bind();
    }
    
    template<class Derived>
    inline void OpenGLBase<Derived>::bind(unsigned int id) noexcept{
        Derived::bind(id);
    }
    
    template<class Derived>
    inline void OpenGLBase<Derived>::unbind() noexcept{
        Derived::unbind();
    }
    
    template<class Derived>
    inline int OpenGLBase<Derived>::getBound() noexcept{
        return Derived::getBound();
    }

    template<class Derived>
    Binder<Derived>::Binder(const OpenGLBase<Derived>& base) noexcept:
        prev(base.getBound())
    {
        base.bind();
    }

    template<class Derived>
    Binder<Derived>::~Binder() noexcept{
        Derived::bind(prev);
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