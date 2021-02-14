#ifndef HGL_OPENGL_BUFFER__H_
#define HGL_OPENGL_BUFFER__H_

#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    enum BufferTarget : unsigned int{
        VertexBuffer            = GL_ARRAY_BUFFER,
        CopyReadBuffer          = GL_COPY_READ_BUFFER,
        CopyWriteBuffer         = GL_COPY_WRITE_BUFFER,
        IndexBuffer             = GL_ELEMENT_ARRAY_BUFFER,
        PixelPackBuffer         = GL_PIXEL_PACK_BUFFER,
        PixelUnpackBuffer       = GL_PIXEL_UNPACK_BUFFER,
        TextureBuffer           = GL_TEXTURE_BUFFER,
        TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
        UniformBuffer           = GL_UNIFORM_BUFFER
    };

    template<BufferTarget target>
    class OpenGLBuffer : public OpenGLBase{
    public:
        OpenGLBuffer();
        ~OpenGLBuffer();
        void bind() const;
        void unbind() const;
        template<typename T>
        void feedData(
            const T* data,
            unsigned int dataCount,
            unsigned int usage);
    };

    #define OpenGLBuffer_feedData_TEMP_INST(target,T)\
        extern template void HERMYGL_EXPORT OpenGLBuffer<target>::feedData<T>(\
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
        extern template class HERMYGL_EXPORT OpenGLBuffer<target>;\
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
#endif
