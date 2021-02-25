#ifndef HGL_BUFFER__H_
#define HGL_BUFFER__H_

#include <vector>
#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    enum BufferTarget : unsigned int{
        VertexBuffer            = GL_ARRAY_BUFFER,
        IndexBuffer             = GL_ELEMENT_ARRAY_BUFFER,
        #if GL_VERSION_2_1
        PixelPackBuffer         = GL_PIXEL_PACK_BUFFER,
        PixelUnpackBuffer       = GL_PIXEL_UNPACK_BUFFER,
        #endif
        #if GL_VERSION_3_0
        CopyWriteBuffer         = GL_COPY_WRITE_BUFFER,
        TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
        #endif
        #if GL_VERSION_3_1
        CopyReadBuffer          = GL_COPY_READ_BUFFER,
        TextureBuffer           = GL_TEXTURE_BUFFER,
        UniformBuffer           = GL_UNIFORM_BUFFER,
        #endif
        #ifdef GL_VERSION_4_0
        DrawIndirectBuffer      = GL_DRAW_INDIRECT_BUFFER,
        #endif
        #if GL_VERSION_4_2
        AtomicCounterBuffer     = GL_ATOMIC_COUNTER_BUFFER,
        #endif
        #if GL_VERSION_4_3
        DispatchIndirectBuffer  = GL_DISPATCH_INDIRECT_BUFFER,
        ShaderStorageBuffer     = GL_SHADER_STORAGE_BUFFER,
        #endif
        #if GL_VERSION_4_4
        QueryBuffer             = GL_QUERY_BUFFER,
        #endif
    };

    enum BufferUsage : unsigned int{
        UseStreamDraw      = GL_STREAM_DRAW,
        UseStreamRead      = GL_STREAM_READ,
        UseStreamCopy      = GL_STREAM_COPY,
        UseStaticDraw      = GL_STATIC_DRAW,
        UseStaticRead      = GL_STATIC_READ,
        UseStaticCopy      = GL_STATIC_COPY,
        UseDynamicDraw     = GL_DYNAMIC_DRAW,
        UseDynamicRead     = GL_DYNAMIC_READ,
        UseDynamicCopy     = GL_DYNAMIC_COPY,
    };
    
    enum Normalized : bool{
        Norm_FALSE = false, Norm_TRUE = true
    };

    struct LayoutElement{
        Dimension dimension;
        Normalized normalized;
    };

    template<BufferTarget target>
    class Buffer : public OpenGLBase{
    public:
        Buffer();
        ~Buffer();
        void bind() const;
        void unbind() const;
        template<typename T>
        void feedData(
            const T* data,
            unsigned int dataCount,
            BufferUsage usage);
        template<typename T>
        void feedData(
            const std::vector<T>& data,
            BufferUsage usage
        );
    };

    void draw(const Buffer<IndexBuffer>& ib, DrawType mode, int count, unsigned int type, const void* index = 0);

}

#include "HermyGL/Buffer.inl"

#endif
