#ifndef HGL_VERTEXARRAY__H_
#define HGL_VERTEXARRAY__H_

#include "HermyGL/OpenGLBase.hpp"
#include "HermyGL/Buffer.hpp"

namespace hgl{

    class HERMYGL_EXPORT VertexArray : public OpenGLBase{
    public:
        VertexArray() noexcept;
        VertexArray(unsigned int id) noexcept;
        ~VertexArray() noexcept;
        virtual void bind() const noexcept;
        static void staticBind(unsigned int anotherID) noexcept;
        virtual void bind(unsigned int anotherID) const noexcept
        {staticBind(anotherID);}
        static void staticUnbind() noexcept;
        virtual void unbind() const noexcept
        {staticUnbind();}
        static int staticGetBound() noexcept;
        virtual int getBound() const noexcept
        {return staticGetBound();}
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