#ifndef HGL_VERTEXARRAY__H_
#define HGL_VERTEXARRAY__H_

#include "HermyGL/OpenGLBase.hpp"
#include "HermyGL/Buffer.hpp"

namespace hgl{

    class VertexArray : public OpenGLBase<VertexArray>{
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

#include "HermyGL/VertexArray.inl"

#endif