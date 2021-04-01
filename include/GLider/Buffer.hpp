#ifndef GLI_BUFFER__H_
#define GLI_BUFFER__H_

#include <vector>
#include <array>
#include "GLider/OpenGLBase.hpp"

namespace gli{

    enum BufferTarget : unsigned int{
        VertexBuffer            = GL_ARRAY_BUFFER,
        IndexBuffer             = GL_ELEMENT_ARRAY_BUFFER,
        PixelPackBuffer         = GL_PIXEL_PACK_BUFFER,
        PixelUnpackBuffer       = GL_PIXEL_UNPACK_BUFFER,
        CopyWriteBuffer         = GL_COPY_WRITE_BUFFER,
        TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
        // #if GL_VERSION_3_1
        CopyReadBuffer          = GL_COPY_READ_BUFFER,
        TextureBuffer           = GL_TEXTURE_BUFFER,
        UniformBuffer           = GL_UNIFORM_BUFFER,
        // #endif
        // #ifdef GL_VERSION_4_0
        DrawIndirectBuffer      = GL_DRAW_INDIRECT_BUFFER,
        // #endif
        // #if GL_VERSION_4_2
        AtomicCounterBuffer     = GL_ATOMIC_COUNTER_BUFFER,
        // #endif
        // #if GL_VERSION_4_3
        DispatchIndirectBuffer  = GL_DISPATCH_INDIRECT_BUFFER,
        ShaderStorageBuffer     = GL_SHADER_STORAGE_BUFFER,
        // #endif
        // #if GL_VERSION_4_4
        QueryBuffer             = GL_QUERY_BUFFER,
        // #endif
    };

    constexpr unsigned int getBufferTargetBinding(BufferTarget target);

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
    class Buffer : public OpenGLBase<Buffer<target>>{
        friend class OpenGLBase<Buffer<target>>;
        Buffer(unsigned int id) noexcept;
        static void bindID(unsigned int id) noexcept;
        static unsigned int getBoundID() noexcept;
    public:
        Buffer() noexcept;
        ~Buffer() noexcept;
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
        template<typename T, std::size_t N>
        void feedData(
            const std::array<T,N>& data,
            BufferUsage usage
        );
        template<typename T>
        void draw(DrawType mode, unsigned int count, int offset = 0) noexcept;
    };

    template<typename T>
    void draw(const Buffer<IndexBuffer>& ib, DrawType mode, unsigned int count, int offset = 0) noexcept;

}

#include "GLider/impl/Buffer.inl"

#endif
