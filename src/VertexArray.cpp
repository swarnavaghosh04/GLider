#include "HermyGL/VertexArray.hpp"

namespace hgl{
    VertexArray::VertexArray(){
        GL_CALL(glGenVertexArrays(1, &(this->id)));
    }

    VertexArray::~VertexArray(){
        GL_CALL(glDeleteVertexArrays(1, &(this->id)));
    }

    inline void VertexArray::bind() const{
        GL_CALL(glBindVertexArray(this->id));
    }

    inline void VertexArray::unbind() const{
        GL_CALL(glBindVertexArray(0));
    }

    template<typename T>
    void VertexArray::readBufferData(
        const VertexBuffer&     vb,
        unsigned int            startingAttribIndex
    ){
        bind();
        vb.bind();

        unsigned int stride = 0;
        for(unsigned int i = 0; i < vb.layoutCount; i++)
            stride += (unsigned int)(vb.layout[i].dimension);
        stride *= sizeof(T);

        unsigned long long offset = 0;
        for(unsigned int i = 0; i < vb.layoutCount; i++){
            GL_CALL(glEnableVertexAttribArray(startingAttribIndex));
            glVertexAttribPointer(
                startingAttribIndex,
                vb.layout[i].dimension,
                primitiveTypeToGLType<T>(),
                vb.layout[i].normalized ? GL_TRUE:GL_FALSE,
                stride,
                (const void*)offset);
            offset += (vb.layout[i].dimension)*sizeof(T);
            startingAttribIndex++;
        }

    }

    #define readBufferData_PARAMS\
        const VertexBuffer&     vb,                     \
        unsigned int            startingAttribIndex = 0

    template void VertexArray::readBufferData<char>(readBufferData_PARAMS);
    template void VertexArray::readBufferData<short>(readBufferData_PARAMS);
    template void VertexArray::readBufferData<int>(readBufferData_PARAMS);
    template void VertexArray::readBufferData<long>(readBufferData_PARAMS);
    template void VertexArray::readBufferData<float>(readBufferData_PARAMS);
    #ifdef INCORPORATE_DOUBLE
    template void VertexArray::readBufferData<double>(readBufferData_PARAMS);
    #endif

    #undef readBufferData_PARAMS

}