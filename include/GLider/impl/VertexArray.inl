#ifndef GLI_VERTEXARRAY__I_
#define GLI_VERTEXARRAY__I_

#include "GLider/VertexArray.hpp"

namespace gli{

    template<OpenGLType T>
    inline void Layout::push(Dimensions dim, bool normalized){
        layout.emplace_back(getOpenGLTypeEnum<T>(), dim, normalized);
    }

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

    // template<OpenGLType T, template<typename, auto...> class stdContainer, auto... args>
    //     requires StdContainer<stdContainer, gli::LayoutElement, args...> && OpenGLType<T>
    // inline void VertexArray::readBufferData(
    //     const Buffer<VertexBuffer>& vb,
    //     const stdContainer<gli::LayoutElement, args...>&    layout,
    //     unsigned int                startingAttribIndex
    // ){
    //     readBufferData<T>(vb, layout.data(), layout.size(), startingAttribIndex);
    // }

}

#endif