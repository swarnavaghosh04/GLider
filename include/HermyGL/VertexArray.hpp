#ifndef HGL_VERTEXARRAY__H_
#define HGL_VERTEXARRAY__H_

#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    template<AllocType dataAllocType>
    class HERMYGL_EXPORT VertexArray : public OpenGLBase<dataAllocType>{

    private:

        unsigned int layoutIndex=0;

    public:

        VertexArray(unsigned short count);
        ~VertexArray();
        inline void bind(unsigned short index) const;
        inline void unbind() const;
    };

}

template<hgl::AllocType dataAllocType>
hgl::VertexArray<dataAllocType>::VertexArray(unsigned short count):
    hgl::OpenGLBase<dataAllocType>(count)
{
    GL_CALL(glGenVertexArrays(count, id));
}

template<hgl::AllocType dataAllocType>
hgl::VertexArray<dataAllocType>::~VertexArray(){
    GL_CALL(glDeleteVertexArrays(count, id));
}

template<hgl::AllocType dataAllocType>
void hgl::VertexArray<dataAllocType>::bind(unsigned short index) const{
    GL_CALL(glBindVertexArray(id[index]));
}

template<hgl::AllocType dataAllocType>
void hgl::VertexArray<dataAllocType>::unbind() const{
    GL_CALL(glBindVertexArray(0));
}

#endif