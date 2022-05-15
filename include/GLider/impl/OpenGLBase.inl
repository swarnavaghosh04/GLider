#ifndef GLI_OPENGL_BASE__I_
#define GLI_OPENGL_BASE__I_

#include "GLider/OpenGLBase.hpp"

namespace gli{

    inline BufferBit operator|(BufferBit a, BufferBit b){
        return static_cast<BufferBit>(
            static_cast<unsigned int>(a) | static_cast<unsigned int>(b)
        );
    }

    template<class Derived>
    OpenGLBase<Derived>::OpenGLBase(unsigned int id) noexcept(!GLI_DEBUG):
        id(id)
    {}

    template<class Derived>
    OpenGLBase<Derived>::OpenGLBase(OpenGLBase<Derived>&& other) noexcept(!GLI_DEBUG)
        : id(other.id)
    {
        other.id = 0;
    }

    template<class Derived>
    OpenGLBase<Derived>& OpenGLBase<Derived>::operator= (OpenGLBase<Derived>&& other) noexcept(!GLI_DEBUG){
        std::swap(id, other.id);
        return *this;
    }

    template<class Derived>
    inline void OpenGLBase<Derived>::bindID(unsigned int id) noexcept(!GLI_DEBUG){
        Derived::bindID(id);
    }

    template<class Derived>
    inline unsigned int OpenGLBase<Derived>::getBoundID() noexcept(!GLI_DEBUG){
        return Derived::getBoundID();
    }
    
    template<class Derived>
    inline void OpenGLBase<Derived>::bind() const noexcept(!GLI_DEBUG){
        bindID(id);
    }
    
    template<class Derived>
    inline void OpenGLBase<Derived>::bind(const OpenGLBase<Derived>& toBeBound) noexcept(!GLI_DEBUG){
        bindID(toBeBound.id);
    }
    
    template<class Derived>
    inline void OpenGLBase<Derived>::unbind() noexcept(!GLI_DEBUG){
        bindID(0);
    }
    
    template<class Derived>
    inline OpenGLBase<Derived> OpenGLBase<Derived>::getBound() noexcept(!GLI_DEBUG){
        return OpenGLBase<Derived>(getBoundID());
    }

    template<class Derived>
    inline bool OpenGLBase<Derived>::isBound() const noexcept(!GLI_DEBUG){
        return (id == getBoundID());
    }

    template<class Derived>
    inline Binder<Derived>::Binder(const OpenGLBase<Derived>& base) noexcept(!GLI_DEBUG):
        prevID{OpenGLBase<Derived>::getBoundID()}
    {
        base.bind();
    }

    template<class Derived>
    inline Binder<Derived>::~Binder() noexcept(!GLI_DEBUG){
        OpenGLBase<Derived>::bindID(prevID);
    }

    inline void clear(BufferBit mask) noexcept(!GLI_DEBUG){
        GL_CALL(glClear(mask));
    }

    inline void enable(Capability_NI cap) noexcept(!GLI_DEBUG){
        GL_CALL(glEnable(cap));
    }

    inline void enable(Capability_I cap) noexcept(!GLI_DEBUG){
        GL_CALL(glEnable(cap));
    }

    inline void enable(Capability_I cap, unsigned int index) noexcept(!GLI_DEBUG){
        GL_CALL(glEnablei(cap, index));
    }

    inline void disable(Capability_NI cap) noexcept(!GLI_DEBUG){
        GL_CALL(glDisable(cap));
    }

    inline void disable(Capability_I cap) noexcept(!GLI_DEBUG){
        GL_CALL(glDisable(cap));
    }

    inline void disable(Capability_I cap, unsigned int index) noexcept(!GLI_DEBUG){
        GL_CALL(glDisablei(cap, index));
    }

    template<std::floating_point T>
    void depthRange(T near, T far) noexcept(!GLI_DEBUG){

        if constexpr(std::is_same<T, float>::value){
            GL_CALL(glDepthRangef(near, far));
        }else{
            GL_CALL(glDepthRange(near,far));
        }
    }

}

#endif