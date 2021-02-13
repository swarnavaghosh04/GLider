#include "HermyGL/OpenGLBase.hpp"

namespace hgl{
    inline const unsigned int& OpenGLBase::getId() const
    { return id; }

    OpenGLBase::~OpenGLBase(){}
}