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
    OpenGLBase<Derived>::OpenGLBase(unsigned int id) noexcept:
        id(id)
    {}

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
    inline void OpenGLBase<Derived>::bindID(unsigned int id) noexcept{
        Derived::bindID(id);
    }

    template<class Derived>
    inline unsigned int OpenGLBase<Derived>::getBoundID() noexcept{
        return Derived::getBoundID();
    }
    
    template<class Derived>
    inline void OpenGLBase<Derived>::bind() const noexcept{
        bindID(id);
    }
    
    template<class Derived>
    inline void OpenGLBase<Derived>::bind(const OpenGLBase<Derived>& toBeBound) noexcept{
        bindID(toBeBound.id);
    }
    
    template<class Derived>
    inline void OpenGLBase<Derived>::unbind() noexcept{
        bindID(0);
    }
    
    template<class Derived>
    inline OpenGLBase<Derived> OpenGLBase<Derived>::getBound() noexcept{
        return OpenGLBase<Derived>(getBoundID());
    }

    template<class Derived>
    inline bool OpenGLBase<Derived>::isBound() const noexcept{
        return (id == getBoundID());
    }

    template<class Derived>
    inline Binder<Derived>::Binder(const OpenGLBase<Derived>& base) noexcept:
        prev(base)
    {
        base.bind();
    }

    template<class Derived>
    inline Binder<Derived>::~Binder() noexcept{
        prev.bind();
    }

    inline void clear(BufferBit mask) noexcept{
        GL_CALL(glClear(mask));
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

    template<typename FLOAT_OR_DOUBLE>
    void depthRange(FLOAT_OR_DOUBLE near, FLOAT_OR_DOUBLE far) noexcept{

        constexpr bool isFloat = std::is_same<FLOAT_OR_DOUBLE, float>();
        constexpr bool isDouble = std::is_same<FLOAT_OR_DOUBLE, double>();

        static_assert(isFloat || isDouble, "Type must be either float or double");

        if constexpr(isFloat){
            GL_CALL(glDepthRangef(near, far));
        }else{
            GL_CALL(glDepthRange(near,far));
        }
    }

}

#endif