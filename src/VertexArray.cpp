#include "GLider/VertexArray.hpp"

namespace gli{

    Layout::Layout(std::vector<Layout::Element>::size_type count){
        layout.reserve(count);
    }

    void VertexArray::readBufferData(
        const Buffer<VertexBuffer>& vb,
        const Layout&               layout,
        unsigned int                startingAttribIndex
    ){

        Binder b1(*this);
        Binder b2(vb);

        int stride = 0;
        for(unsigned int i = 0; i < layout.layout.size(); i++)
            stride += (int)(layout.layout[i].count*getSizeOfOpenGLType(layout.layout[i].type));

        unsigned long long offset = 0;
        for(unsigned int i = 0; i < layout.layout.size(); i++){
            GL_CALL(glEnableVertexAttribArray(startingAttribIndex));
            GL_CALL(glVertexAttribPointer(
                startingAttribIndex,
                (int)(layout.layout[i].count),
                layout.layout[i].type,
                layout.layout[i].normalized ? GL_TRUE:GL_FALSE,
                stride,
                (const void*)offset)
            );
            offset += (layout.layout[i].count)*getSizeOfOpenGLType(layout.layout[i].type);
            startingAttribIndex++;
        }

    }
}