#ifndef GLI_VERTEXARRAY__I_
#define GLI_VERTEXARRAY__I_

#include "GLider/VertexArray.hpp"

namespace gli{

    inline VertexArray::VertexArray() noexcept
    {
        GL_CALL(glGenVertexArrays(1, &(this->id)));
    }

    inline VertexArray::~VertexArray() noexcept
    {
        GL_CALL(glDeleteVertexArrays(1, &(this->id)));
    }

    inline void VertexArray::draw(DrawType mode, int first, int count) const noexcept
    {
        GL_CALL(glDrawArrays(static_cast<unsigned int>(mode), first, count));
    }

    inline void VertexArray::bind() const noexcept{
        GL_CALL(glBindVertexArray(this->id));
    }

    inline void VertexArray::bind(unsigned int id) noexcept{
        GL_CALL(glBindVertexArray(id));
    }

    inline void VertexArray::unbind() noexcept{
        GL_CALL(glBindVertexArray(0));
    }

    inline int VertexArray::getBound() noexcept{
        int r;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &r);
        return r;
    }

    template<typename T>
    void VertexArray::readBufferData(
        const Buffer<VertexBuffer>& vb,
        const LayoutElement*        layout,
        unsigned int                layoutCount,
        unsigned int                startingAttribIndex
    ){

        Binder b1(*this);
        Binder b2(vb);

        int stride = 0;
        for(unsigned int i = 0; i < layoutCount; i++)
            stride += (int)(layout[i].dimension);
        stride *= sizeof(T);

        unsigned long long offset = 0;
        for(unsigned int i = 0; i < layoutCount; i++){
            GL_CALL(glEnableVertexAttribArray(startingAttribIndex));
            GL_CALL(glVertexAttribPointer(
                startingAttribIndex,
                (int)(layout[i].dimension),
                getOpenGLTypeEnum<T>(),
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

    template<typename T, std::size_t N>
    inline void VertexArray::readBufferData(
        const Buffer<VertexBuffer>&         vb,
        const std::array<LayoutElement, N>& layout,
        unsigned int                        startingAttribIndex
    ){
        readBufferData<T>(vb, layout.data(), layout.size(), startingAttribIndex);
    }

}

#endif