#ifndef HGL_VERTEXARRAY__H_
#define HGL_VERTEXARRAY__H_

#include "HermyGL/OpenGLBase.hpp"
#include "HermyGL/Buffer.hpp"

namespace hgl{

    class HERMYGL_EXPORT VertexArray : public OpenGLBase{
    public:
        VertexArray() noexcept;
        ~VertexArray() noexcept;
        void bind() const noexcept;
        void unbind() const noexcept;
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