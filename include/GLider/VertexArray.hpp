#ifndef GLI_VERTEXARRAY__H_
#define GLI_VERTEXARRAY__H_

#include "GLider/OpenGLBase.hpp"
#include "GLider/Buffer.hpp"
#include <vector>

namespace gli{
    
    enum Dimensions : unsigned int{
        D1 = 1, D2, D3, D4
    };

    class Layout{
    private:
        friend class VertexArray;
        struct Element{
            OpenGLTypes type;
            Dimensions count;
            bool normalized;
        };
        std::vector<Element> layout;
    public:
        Layout() noexcept = default;
        Layout(std::vector<Layout::Element>::size_type count);
        template<OpenGLType T>
        void push(Dimensions count, bool normalized);
    };

    class VertexArray : public OpenGLBase<VertexArray>{
        friend class OpenGLBase<VertexArray>;
        VertexArray(unsigned int id) noexcept;
        static void bindID(unsigned int id) noexcept;
        static unsigned int getBoundID() noexcept;
    public:
        VertexArray() noexcept;
        ~VertexArray() noexcept;
        void readBufferData(
            const Buffer<VertexBuffer>& vb,
            const Layout&               layout,
            unsigned int                startingAttribIndex = 0
        );
        // template<OpenGLType T, template<typename, auto...> class stdContainer, auto... args>
        //     requires StdContainer<stdContainer, gli::LayoutElement, args...> && OpenGLType<T>
        // void readBufferData(
        //     const Buffer<VertexBuffer>&                         vb,
        //     const stdContainer<gli::LayoutElement, args...>&    layout,
        //     unsigned int                                        startingAttribIndex = 0
        // );
        void draw(DrawType mode, int first, int count) const noexcept;
    };

}

#include "GLider/impl/VertexArray.inl"

#endif