#ifndef HGL_OPENGL_BASE__I_
#define HGL_OPENGL_BASE__I_

#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    inline BufferBit operator|(BufferBit a, BufferBit b){
        return static_cast<BufferBit>(
            static_cast<unsigned int>(a) | static_cast<unsigned int>(b)
        );
    }

    template<typename T>
    OpenGLBase<T>::OpenGLBase(OpenGLBase&& other) noexcept
        : id(other.id)
    {
        other.id = 0;
    }

    template<typename T>
    OpenGLBase<T>& OpenGLBase<T>::operator= (OpenGLBase<T>&& other) noexcept{
        std::swap(id, other.id);
        return *this;
    }
    
    template<typename T>
    inline void OpenGLBase<T>::bind() const noexcept{
        ((T*)(this))->bind();
    }
    
    template<typename T>
    inline void OpenGLBase<T>::bind(unsigned int id) noexcept{
        T::bind(id);
    }
    
    template<typename T>
    inline void OpenGLBase<T>::unbind() noexcept{
        T::unbind();
    }
    
    template<typename T>
    inline int OpenGLBase<T>::getBound() noexcept{
        return T::getBound();
    }

    template<typename T>
    Binder<T>::Binder(const OpenGLBase<T>& base) noexcept:
        prev(base.getBound())
    {
        base.bind();
    }

    template<typename T>
    Binder<T>::~Binder() noexcept{
        T::bind(prev);
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