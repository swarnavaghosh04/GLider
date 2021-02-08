#ifndef HGL_VERTEXBUFFER__H_
#define HGL_VERTEXBUFFER__H_

#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    struct LayoutElement{
        unsigned short count;
        bool normalized;
    };

    template<typename T, AllocType dataAllocType>
    class HERMYGL_EXPORT VertexBuffer : public OpenGLBase<dataAllocType>{

    public:
        VertexBuffer();
        ~VertexBuffer();
        inline void bind(unsigned short index) const;
        inline void unbind() const;
    };

}

template<typename T, hgl::AllocType dataAllocType>
hgl::VertexBuffer<T, dataAllocType>::VertexBuffer(unsigned short count):
    hgl::OpenGLBase<dataAllocType>(count)
{
    GL_CALL(glGenBuffers(count, id));
}

template<typename T, hgl::AllocType dataAllocType>
hgl::VertexBuffer<T, dataAllocType>::~VertexBuffer(){
    GL_CALL(glDeleteBuffers(count, id));
}

template<typename T, hgl::AllocType dataAllocType>
hgl::VertexBuffer<T, dataAllocType>::bind(unsigned short index) const{
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, id[index]));
}

template<typename T, hgl::AllocType dataAllocType>
hgl::VertexBuffer<T, dataAllocType>::unbind() const{
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

#endif