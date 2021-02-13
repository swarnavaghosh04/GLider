#include "HermyGL/VertexBuffer.hpp"

namespace hgl{
    VertexBuffer::VertexBuffer(){
        GL_CALL(glGenBuffers(1, &(this->id)));
    }

    VertexBuffer::~VertexBuffer(){
        GL_CALL(glDeleteBuffers(1, &(this->id)));
    }

    inline void VertexBuffer::bind() const{
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, this->id));
    }

    inline void VertexBuffer::unbind() const{
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
    
    template<typename T>
    void VertexBuffer::feedData(
        const T* data,
        unsigned int dataCount,
        const LayoutElement* layout,
        unsigned int layoutCount,
        unsigned int usage
    ){
        bind();
        this->layout = layout;
        this->layoutCount = layoutCount;
        GL_CALL(glBufferData(GL_ARRAY_BUFFER, dataCount*sizeof(T), data, usage));
    }

    #define feedData_PARAMS(T)          \
        const T* data,                  \
        unsigned int count,             \
        const LayoutElement* layout,    \
        unsigned int layoutCount,       \
        unsigned int usage

    template void VertexBuffer::feedData<char>(feedData_PARAMS(char));
    template void VertexBuffer::feedData<short>(feedData_PARAMS(short));
    template void VertexBuffer::feedData<int>(feedData_PARAMS(int));
    template void VertexBuffer::feedData<long>(feedData_PARAMS(long));
    template void VertexBuffer::feedData<float>(feedData_PARAMS(float));
    #ifdef INCORPORATE_DOUBLE
    template void VertexBuffer::feedData<double>(feedData_PARAMS(double));
    #endif

    #undef feedData_PARAMS

}