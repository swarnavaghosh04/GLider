#ifndef HGL_VERTEXARRAY__I_
#define HGL_VERTEXARRAY__I_

#include "HermyGL/VertexArray.hpp"

namespace hgl{

    inline void VertexArray::bind() const{
        GL_CALL(glBindVertexArray(this->id));
    }

    inline void VertexArray::unbind() const{
        GL_CALL(glBindVertexArray(0));
    }

    template<typename T>
    inline void VertexArray::readBufferData(
        const Buffer<VertexBuffer>& vb,
        const LayoutElement*        layout,
        unsigned int                layoutCount,
        unsigned int                startingAttribIndex
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
            startingAttribIndex++;
        }

    }

    template<typename T>
    inline void VertexArray::readBufferData(
        const Buffer<VertexBuffer>&         vb,
        const std::vector<LayoutElement>&   layout,
        unsigned int                        startingAttribIndex
    ){
        readBufferData<T>(vb, layout.data(), layout.size(), startingAttribIndex);
    }

}

#endif