#ifndef GLI_VERTEXARRAY__I_
#define GLI_VERTEXARRAY__I_

#include "GLider/VertexArray.hpp"

namespace gli{

    inline VertexArray::VertexArray() noexcept
    {
        GL_CALL(glGenVertexArrays(1, &(this->id)));
    }

    inline VertexArray::VertexArray(unsigned int id) noexcept:
        OpenGLBase(id)
    {}

    inline VertexArray::~VertexArray() noexcept
    {
        GL_CALL(glDeleteVertexArrays(1, &(this->id)));
    }

    inline void VertexArray::draw(DrawType mode, int first, int count) const noexcept
    {
        GL_CALL(glDrawArrays(static_cast<unsigned int>(mode), first, count));
    }

    inline void VertexArray::bindID(unsigned int id) noexcept{
        GL_CALL(glBindVertexArray(id));
    }

    inline unsigned int VertexArray::getBoundID() noexcept{
        int r;
        GL_CALL(glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &r));
        return static_cast<unsigned int>(r);
    }

    template<OpenGLType T>
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

    template<OpenGLType T, template<typename, auto...> class stdContainer, auto... args>
        requires StdContainer<stdContainer, gli::LayoutElement, args...> && OpenGLType<T>
    inline void VertexArray::readBufferData(
        const Buffer<VertexBuffer>& vb,
        const stdContainer<gli::LayoutElement, args...>&    layout,
        unsigned int                startingAttribIndex
    ){
        readBufferData<T>(vb, layout.data(), layout.size(), startingAttribIndex);
    }

}

#endif