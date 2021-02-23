#ifndef HGL_VERTEXARRAY__H_
#define HGL_VERTEXARRAY__H_

#include "HermyGL/OpenGLBase.hpp"
#include "HermyGL/Buffer.hpp"

namespace hgl{

    class VertexArray : public OpenGLBase{
    public:
        VertexArray();
        ~VertexArray();
        void bind() const;
        void unbind() const;
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
        void draw(DrawType mode, int first, int count) const;
    };

}

#include "HermyGL/VertexArray.inl"

#endif