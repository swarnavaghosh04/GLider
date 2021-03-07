#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    OpenGLBase::OpenGLBase(OpenGLBase&& other) noexcept
        : id(other.id)
    {
        other.id = 0;
    }

    OpenGLBase& OpenGLBase::operator= (OpenGLBase&& other) noexcept{
        std::swap(id, other.id);
        return *this;
    }

    Binder::Binder(const OpenGLBase& base) noexcept:
        base(base),
        prev(base.getBound())
    {
        base.bind();
    }

    Binder::~Binder() noexcept{
        base.bind(prev);
    }

}