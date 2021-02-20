#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    void clear(unsigned int mask){
        GL_CALL(glClear(mask);)
    }

    inline const unsigned int& OpenGLBase::getId() const
    { return id; }

    OpenGLBase::~OpenGLBase(){}
}