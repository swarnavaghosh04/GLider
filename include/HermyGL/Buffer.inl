#ifndef HGL_BUFFER__I_
#define HGL_BUFFER__I_

#include "HermyGL/Buffer.hpp"

namespace hgl{

    template<BufferTarget target>
    Buffer<target>::Buffer() noexcept{
        GL_CALL(glGenBuffers(1, &(this->id)));
    }

    template<BufferTarget target>
    Buffer<target>::~Buffer() noexcept{
        GL_CALL(glDeleteBuffers(1, &(this->id)));
    }

    template<BufferTarget target>
    inline void Buffer<target>::bind() const noexcept{
        GL_CALL(glBindBuffer((unsigned int)target, this->id));
    }

    template<BufferTarget target>
    inline void Buffer<target>::unbind() const noexcept{
        GL_CALL(glBindBuffer((unsigned int)target, 0));
    }

    template<BufferTarget target>
    template<typename T>
    inline void Buffer<target>::feedData(
        const T* data,
        unsigned int dataCount,
        BufferUsage usage
    ){
        bind();
        GL_CALL(glBufferData(target, dataCount*sizeof(T), data, usage));
    }

    template<BufferTarget target>
    template<typename T>
    inline void Buffer<target>::feedData(
        const std::vector<T>& data,
        BufferUsage usage
    ){
        bind();
        GL_CALL(glBufferData(target, data.size()*sizeof(T), data.data(), usage));
    }

    template<BufferTarget target>
    template<typename T, std::size_t N>
    inline void Buffer<target>::feedData(
        const std::array<T,N>& data,
        BufferUsage usage
    ){
        bind();
        GL_CALL(glBufferData(target, data.size()*sizeof(T), data.data(), usage));
    }

    

    template<BufferTarget target>
    template<typename T>
    inline void Buffer<target>::draw(
        DrawType mode, unsigned int count, int offset
    ) noexcept {
        static_assert((target == IndexBuffer), "Invalid draw call!");
        bind();
        GL_CALL(glDrawElements(mode, count, getOpenGLTypeEnum<T>(), reinterpret_cast<void*>(offset*sizeof(T))));
    }

    template<typename T>
    inline void draw(const Buffer<IndexBuffer>& ib, DrawType mode, unsigned int count, int offset) noexcept{
        GL_CALL(glDrawElements(mode, count, getOpenGLTypeEnum<T>(), reinterpret_cast<void*>(offset*sizeof(T))));
    }

}

#endif