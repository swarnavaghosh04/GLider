#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    OpenGLBase::OpenGLBase(OpenGLBase&& other) noexcept(true)
        : id(other.id)
    {
        other.id = 0;
    }

    OpenGLBase& OpenGLBase::operator= (OpenGLBase&& other) noexcept(true){
        std::swap(id, other.id);
        return *this;
    }

}