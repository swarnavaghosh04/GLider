#ifndef HGL_BUFFER__I_
#define HGL_BUFFER__I_

#include "HermyGL/Buffer.hpp"

namespace hgl{

    template<BufferTarget target>
    Buffer<target>::Buffer(){
        GL_CALL(glGenBuffers(1, &(this->id)));
    }

    template<BufferTarget target>
    Buffer<target>::~Buffer(){
        GL_CALL(glDeleteBuffers(1, &(this->id)));
    }

    template<BufferTarget target>
    inline void Buffer<target>::bind() const{
        GL_CALL(glBindBuffer((unsigned int)target, this->id));
    }

    template<BufferTarget target>
    inline void Buffer<target>::unbind() const{
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

    inline void draw(const Buffer<IndexBuffer>& ib, DrawType mode, int count, unsigned int type, const void* index){
        GL_CALL(glDrawElements(mode, count, type, index));
    }

}

#endif