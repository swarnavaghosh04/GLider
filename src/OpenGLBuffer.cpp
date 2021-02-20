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
        BufferUsage usage
    ){
        bind();
        GL_CALL(glBufferData(target, dataCount*sizeof(T), data, usage));
    }

    #define OpenGLBuffer_feedData_TEMP_INST(T,target)\
        template void OpenGLBuffer<target>::feedData<T>(\
            const T* data,\
            unsigned int dataCount,\
            BufferUsage usage)

    #define OpenGLBuffer_TEMP_INST(target)\
        template class OpenGLBuffer<target>;\
        __HGL_InstantiateTemplateTypes(OpenGLBuffer_feedData_TEMP_INST, target);

    OpenGLBuffer_TEMP_INST(VertexBuffer);
    OpenGLBuffer_TEMP_INST(IndexBuffer);
    #if GL_VERSION_2_1
    OpenGLBuffer_TEMP_INST(PixelPackBuffer);
    OpenGLBuffer_TEMP_INST(PixelUnpackBuffer);
    #endif
    #if GL_VERSION_3_0
    OpenGLBuffer_TEMP_INST(CopyWriteBuffer);
    OpenGLBuffer_TEMP_INST(TransformFeedbackBuffer);
    #endif
    #if GL_VERSION_3_1
    OpenGLBuffer_TEMP_INST(CopyReadBuffer);
    OpenGLBuffer_TEMP_INST(TextureBuffer);
    OpenGLBuffer_TEMP_INST(UniformBuffer);
    #endif
    #ifdef GL_VERSION_4_0
    OpenGLBuffer_TEMP_INST(DrawIndirectBuffer);
    #endif
    #if GL_VERSION_4_2
    OpenGLBuffer_TEMP_INST(AtomicCounterBuffer);
    #endif
    #if GL_VERSION_4_3
    OpenGLBuffer_TEMP_INST(DispatchIndirectBuffer);
    OpenGLBuffer_TEMP_INST(ShaderStorageBuffer);
    #endif
    #if GL_VERSION_4_4
    OpenGLBuffer_TEMP_INST(QueryBuffer);
    #endif

    #undef OpenGLBuffer_TEMP_INST
    #undef OpenGLBuffer_feedData_TEMP_INST

    void draw(const OpenGLBuffer<IndexBuffer>& ib, DrawType mode, int count, unsigned int type, const void* index){
        GL_CALL(glDrawElements(mode, count, type, index));
    }

}