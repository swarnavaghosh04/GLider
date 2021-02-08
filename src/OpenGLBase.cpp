#include "HermyGL/OpenGLBase.hpp"

template<hgl::AllocType dataAllocType>
hgl::OpenGLBase<dataAllocType>::OpenGLBase(unsigned short count):
    count(count)
{
    if(dataAllocType == hgl::AllocType::heap) id = new unsigned int[count];
    else id[count] = {};
}

template<hgl::AllocType dataAllocType>
hgl::OpenGLBase<dataAllocType>::~OpenGLBase(){
    if(dataAllocType == hgl::AllocType::heap) delete[] id;
}
