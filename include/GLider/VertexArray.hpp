#ifndef GLI_VERTEXARRAY__H_
#define GLI_VERTEXARRAY__H_

#include "GLider/OpenGLBase.hpp"
#include "GLider/Buffer.hpp"

namespace gli{

    class VertexArray : public OpenGLBase<VertexArray>{
        friend class OpenGLBase<VertexArray>;
        VertexArray(unsigned int id) noexcept;
        static void bindID(unsigned int id) noexcept;
        static unsigned int getBoundID() noexcept;
    public:
        VertexArray() noexcept;
        ~VertexArray() noexcept;
        template<OpenGLType T>
        void readBufferData(
            const Buffer<VertexBuffer>& vb,
            const LayoutElement*        layout,
            unsigned int                layoutCount,
            unsigned int                startingAttribIndex = 0
        );
        template<OpenGLType T, template<typename, auto...> class stdContainer, auto... args>
            requires StdContainer<stdContainer, gli::LayoutElement, args...> && OpenGLType<T>
        void readBufferData(
            const Buffer<VertexBuffer>&                         vb,
            const stdContainer<gli::LayoutElement, args...>&    layout,
            unsigned int                                        startingAttribIndex = 0
        );
        void draw(DrawType mode, int first, int count) const noexcept;
    };

}

#include "GLider/impl/VertexArray.inl"

#endif