#include "HermyGL/OpenGLBuffer.hpp"

namespace hgl{

    template<BufferTarget target>
    OpenGLBuffer<target>::OpenGLBuffer(){
        GL_CALL(glGenBuffers(1, &(this->id)));
    }

    template<BufferTarget target>
    OpenGLBuffer<target>::~OpenGLBuffer(){
        GL_CALL(glDeleteBuffers(1, &(this->id)));
    }

    template<BufferTarget target>
    void OpenGLBuffer<target>::bind() const{
        GL_CALL(glBindBuffer((unsigned int)target, this->id));
    }

    template<BufferTarget target>
    void OpenGLBuffer<target>::unbind() const{
        GL_CALL(glBindBuffer((unsigned int)target, 0));
    }

    template<BufferTarget target>
    template<typename T>
    void OpenGLBuffer<target>::feedData(
        const T* data,
        unsigned int dataCount,
        unsigned int usage
    ){
        bind();
        GL_CALL(glBufferData(target, dataCount*sizeof(T), data, usage));
    }

    #define OpenGLBuffer_feedData_TEMP_INST(target,T)\
        template void OpenGLBuffer<target>::feedData<T>(\
            const T* data,\
            unsigned int dataCount,\
            unsigned int usage)

    #ifdef INCORPORATE_DOUBLE
        #define OpenGLBuffer_feedData_TEMP_INST_DOUBLE(target)\
            OpenGLBuffer_feedData_TEMP_INST(target,double)
    #else
        #define OpenGLBuffer_feedData_TEMP_INST_DOUBLE(target)
    #endif
    
    #define OpenGLBuffer_TEMP_INST(target)\
        template class OpenGLBuffer<target>;\
        OpenGLBuffer_feedData_TEMP_INST(target, char);\
        OpenGLBuffer_feedData_TEMP_INST(target, unsigned char);\
        OpenGLBuffer_feedData_TEMP_INST(target, short);\
        OpenGLBuffer_feedData_TEMP_INST(target, unsigned short);\
        OpenGLBuffer_feedData_TEMP_INST(target, int);\
        OpenGLBuffer_feedData_TEMP_INST(target, unsigned int);\
        OpenGLBuffer_feedData_TEMP_INST(target, long);\
        OpenGLBuffer_feedData_TEMP_INST(target, unsigned long);\
        OpenGLBuffer_feedData_TEMP_INST(target, float);\
        OpenGLBuffer_feedData_TEMP_INST_DOUBLE(target)

    OpenGLBuffer_TEMP_INST(BufferTarget::VertexBuffer);
    OpenGLBuffer_TEMP_INST(BufferTarget::CopyReadBuffer);
    OpenGLBuffer_TEMP_INST(BufferTarget::CopyWriteBuffer);
    OpenGLBuffer_TEMP_INST(BufferTarget::IndexBuffer);
    OpenGLBuffer_TEMP_INST(BufferTarget::PixelPackBuffer);
    OpenGLBuffer_TEMP_INST(BufferTarget::PixelUnpackBuffer);
    OpenGLBuffer_TEMP_INST(BufferTarget::TextureBuffer);
    OpenGLBuffer_TEMP_INST(BufferTarget::TransformFeedbackBuffer);
    OpenGLBuffer_TEMP_INST(BufferTarget::UniformBuffer);

    #undef OpenGLBuffer_TEMP_INST
    #undef OpenGLBuffer_feedData_TEMP_INST_DOUBLE
    #undef OpenGLBuffer_feedData_TEMP_INST

}