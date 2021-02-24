#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    //RuntimeOpenGLBase::RuntimeOpenGLBase(){}
    RuntimeOpenGLBase::~RuntimeOpenGLBase(){}

    RuntimeOpenGLBase::RuntimeOpenGLBase(RuntimeOpenGLBase&& other) noexcept(true):
        id(other.id)
    {
        other.id = 0;
    }

    RuntimeOpenGLBase& RuntimeOpenGLBase::operator= (RuntimeOpenGLBase&& other) noexcept(true){
        std::swap(id, other.id);
        return *this;
    }

}