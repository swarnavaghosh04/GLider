#ifndef GLI_BUFFER__I_
#define GLI_BUFFER__I_

#include "GLider/Buffer.hpp"

namespace gli{

    constexpr unsigned int getBufferTargetBinding(BufferTarget target){
        switch(target){
        case VertexBuffer:
            return GL_ARRAY_BUFFER_BINDING;
        case IndexBuffer:
            return GL_ELEMENT_ARRAY_BUFFER_BINDING;
        case PixelPackBuffer:
            return GL_PIXEL_PACK_BUFFER_BINDING;
        case PixelUnpackBuffer:
            return GL_PIXEL_UNPACK_BUFFER_BINDING;
        case CopyWriteBuffer:
            return GL_COPY_WRITE_BUFFER_BINDING;
        case TransformFeedbackBuffer:
            return GL_TRANSFORM_FEEDBACK_BUFFER_BINDING;
        // #if GL_VERSION_3_1
        case CopyReadBuffer:
            return GL_COPY_READ_BUFFER_BINDING;
        case TextureBuffer:
            return GL_TEXTURE_BUFFER_BINDING;
        case UniformBuffer:
            return GL_UNIFORM_BUFFER_BINDING;
        // #endif
        // #ifdef GL_VERSION_4_0
        case DrawIndirectBuffer:
            return GL_DRAW_INDIRECT_BUFFER_BINDING;
        // #endif
        // #if GL_VERSION_4_2
        case AtomicCounterBuffer:
            return GL_ATOMIC_COUNTER_BUFFER_BINDING;
        // #endif
        // #if GL_VERSION_4_3
        case DispatchIndirectBuffer:
            return GL_DISPATCH_INDIRECT_BUFFER_BINDING;
        case ShaderStorageBuffer:
            return GL_SHADER_STORAGE_BUFFER_BINDING;
        // #endif
        // #if GL_VERSION_4_4
        case QueryBuffer:
            return GL_QUERY_BUFFER_BINDING;
        // #endif
        }
        throw std::logic_error("Invalid Buffer Target Binding");
    }

    template<BufferTarget target>
    Buffer<target>::Buffer() noexcept{
        GL_CALL(glGenBuffers(1, &(this->id)));
    }
    
    template<BufferTarget target>
    inline Buffer<target>::Buffer(unsigned int id) noexcept:
        OpenGLBase<Buffer<target>>(id)
    {}

    template<BufferTarget target>
    Buffer<target>::~Buffer() noexcept{
        GL_CALL(glDeleteBuffers(1, &(this->id)));
    }

    template<BufferTarget target>
    inline void Buffer<target>::bindID(unsigned int id) noexcept{
        GL_CALL(glBindBuffer((unsigned int)target, id));
    }
    
    template<BufferTarget target>
    inline unsigned int Buffer<target>::getBoundID() noexcept{
        int r;
        GL_CALL(glGetIntegerv(getBufferTargetBinding(target), &r));
        return static_cast<unsigned int>(r);
    }

    template<BufferTarget target>
    template<typename T>
    inline void Buffer<target>::feedData(
        const T* data,
        unsigned int dataCount,
        BufferUsage usage
    ){
        Binder b(*this);
        GL_CALL(glBufferData(target, dataCount*sizeof(T), data, usage));
    }

    template<BufferTarget target>
    template<typename T>
    inline void Buffer<target>::feedData(
        const std::vector<T>& data,
        BufferUsage usage
    ){
        Binder b(*this);
        GL_CALL(glBufferData(target, data.size()*sizeof(T), data.data(), usage));
    }

    template<BufferTarget target>
    template<typename T, std::size_t N>
    inline void Buffer<target>::feedData(
        const std::array<T,N>& data,
        BufferUsage usage
    ){
        Binder b(*this);
        GL_CALL(glBufferData(target, N*sizeof(T), data.data(), usage));
    }

    template<BufferTarget target>
    template<typename T>
    inline void Buffer<target>::draw(
        DrawType mode, unsigned int count, int offset
    ) noexcept {
        static_assert((target == IndexBuffer), "Invalid draw call!");
        Binder b(*this);
        GL_CALL(glDrawElements(mode, count, getOpenGLTypeEnum<T>(), reinterpret_cast<void*>(offset*sizeof(T))));
    }

    template<typename T>
    inline void draw(const Buffer<IndexBuffer>& ib, DrawType mode, unsigned int count, int offset) noexcept{
        Binder b(ib);
        GL_CALL(glDrawElements(mode, count, getOpenGLTypeEnum<T>(), reinterpret_cast<void*>(offset*sizeof(T))));
    }

}

#endif