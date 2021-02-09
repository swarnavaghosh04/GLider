#ifndef HGL_VERTEXBUFFER__H_
#define HGL_VERTEXBUFFER__H_

#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    template<AllocType allocType = AllocType::heap>
    class HERMYGL_EXPORT VertexBuffer : public OpenGLBase<allocType>{
    public:
        VertexBuffer(unsigned short count = 1,unsigned int* buf = nullptr);
        ~VertexBuffer();
        void bind(unsigned short index = 0) const;
        void unbind() const;
        template<typename T>
        void feedData(const T* data, unsigned int count, unsigned int usage, unsigned short index = 0);
    };

    template<AllocType allocType>
    VertexBuffer<allocType>::VertexBuffer(unsigned short count, unsigned int* buf):
        OpenGLBase<allocType>(count, buf)
    {
        GL_CALL(glGenBuffers(this->count, this->id));
    }

    template<AllocType allocType>
    VertexBuffer<allocType>::~VertexBuffer(){
        GL_CALL(glDeleteBuffers(this->count, this->id));
    }

    template<AllocType allocType>
    inline void VertexBuffer<allocType>::bind(unsigned short index) const{
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, this->id[index]));
    }

    template<AllocType allocType>
    inline void VertexBuffer<allocType>::unbind() const{
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    template<AllocType allocType>
    template<typename T>
    void VertexBuffer<allocType>::feedData(const T* data, unsigned int dataCount, unsigned int usage, unsigned short index){
        bind(index);
        GL_CALL(glBufferData(GL_ARRAY_BUFFER, dataCount*sizeof(T), data, usage));
    }

}



#endif