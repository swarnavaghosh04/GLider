#ifndef GLI_VERTEXARRAY__H_
#define GLI_VERTEXARRAY__H_

#include "GLider/OpenGLBase.hpp"
#include "GLider/Buffer.hpp"

namespace gli{

    class VertexArray : public OpenGLBase<VertexArray>{
        friend class OpenGLBase<VertexArray>;
    public:
        VertexArray() noexcept;
        VertexArray(unsigned int id) noexcept;
        ~VertexArray() noexcept;
        void bind() const noexcept;
        static void bind(unsigned int id) noexcept;
        static void unbind() noexcept;
        static int getBound() noexcept;
        template<typename T>
        void readBufferData(
            const Buffer<VertexBuffer>& vb,
            const LayoutElement*        layout,
            unsigned int                layoutCount,
            unsigned int                startingAttribIndex = 0
        );
        template<typename T>
        void readBufferData(
            const Buffer<VertexBuffer>&         vb,
            const std::vector<LayoutElement>&   layout,
            unsigned int                        startingAttribIndex = 0
        );
        template<typename T, std::size_t N>
        void readBufferData(
            const Buffer<VertexBuffer>&         vb,
            const std::array<LayoutElement, N>& layout,
            unsigned int                        startingAttribIndex = 0
        );
        void draw(DrawType mode, int first, int count) const noexcept;
    };

}

#include "GLider/impl/VertexArray.inl"

#endif