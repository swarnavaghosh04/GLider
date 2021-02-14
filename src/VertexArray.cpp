#include "HermyGL/VertexArray.hpp"

namespace hgl{
    VertexArray::VertexArray(){
        GL_CALL(glGenVertexArrays(1, &(this->id)));
    }

    VertexArray::~VertexArray(){
        GL_CALL(glDeleteVertexArrays(1, &(this->id)));
    }

    void VertexArray::bind() const{
        GL_CALL(glBindVertexArray(this->id));
    }

    void VertexArray::unbind() const{
        GL_CALL(glBindVertexArray(0));
    }

    template<typename T>
    void VertexArray::readBufferData(
        const OpenGLBuffer<VertexBuffer>&   vb,
        const LayoutElement*                layout,
        unsigned int                        layoutCount,
        unsigned int                        startingAttribIndex
    ){
        bind();
        vb.bind();

        int stride = 0;
        for(int i = 0; i < layoutCount; i++)
            stride += (int)(layout[i].dimension);
        stride *= sizeof(T);

        unsigned long long offset = 0;
        for(unsigned int i = 0; i < layoutCount; i++){
            GL_CALL(glEnableVertexAttribArray(startingAttribIndex));
            GL_CALL(glVertexAttribPointer(
                startingAttribIndex,
                (int)(layout[i].dimension),
                primitiveTypeToGLType<T>(),
                layout[i].normalized ? GL_TRUE:GL_FALSE,
                stride,
                (const void*)offset)
            );
            offset += (layout[i].dimension)*sizeof(T);
            GL_CALL(glDisableVertexAttribArray(startingAttribIndex));
            startingAttribIndex++;
        }

    }


    #define TEMP_INST(T)\
        template void VertexArray::readBufferData<T>(\
            const OpenGLBuffer<VertexBuffer>&   vb,\
            const LayoutElement*                layout,\
            unsigned int                        layoutCount,\
            unsigned int                        startingAttribIndex = 0\
        )

    TEMP_INST(char);
    TEMP_INST(unsigned char);
    TEMP_INST(short);
    TEMP_INST(unsigned short);
    TEMP_INST(int);
    TEMP_INST(unsigned int);
    TEMP_INST(long);
    TEMP_INST(unsigned long);
    TEMP_INST(float);
    #ifdef INCORPORATE_DOUBLE
    TEMP_INST(double);
    #endif

    #undef TEMP_INST

}