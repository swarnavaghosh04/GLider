#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    void clear(unsigned int mask){
        GL_CALL(glClear(mask);)
    }

    OpenGLBase::OpenGLBase(OpenGLBase&& other) noexcept(true):
        id(other.id)
    {
        other.id = 0;
    }

    OpenGLBase& OpenGLBase::operator= (OpenGLBase&& other) noexcept(true){
        std::swap(id, other.id);
        return *this;
    }

    inline const unsigned int OpenGLBase::getId() const
    { return id; }

    OpenGLBase::~OpenGLBase(){}
}