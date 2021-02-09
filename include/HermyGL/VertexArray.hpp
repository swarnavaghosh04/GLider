#ifndef HGL_VERTEXARRAY__H_
#define HGL_VERTEXARRAY__H_

#include "HermyGL/OpenGLBase.hpp"
#include "HermyGL/VertexBuffer.hpp"

namespace hgl{

    struct LayoutElement{
        enum Dimension : unsigned char{
            ONE = 1, TWO = 2, THREE = 3, FOUR = 4
        };
        Dimension dimension;
        bool normalized;
    };

    struct Layout{

        LayoutElement* elements;
        unsigned short count;

        const LayoutElement& operator[] (unsigned int index) { return elements[index]; }
    };

    // inline const LayoutElement& Layout::operator[](unsigned int index)
    // { return elements[index]; }

    template<AllocType allocType = AllocType::heap>
    class HERMYGL_EXPORT VertexArray : public OpenGLBase<allocType>{
    public:
        VertexArray(unsigned short count = 1, unsigned int* buf = nullptr);
        ~VertexArray();
        void bind(unsigned short index = 0) const;
        void unbind() const;
        template<typename T, AllocType _allocType>
        void readBufferData(
            const VertexBuffer<_allocType>& vb,
            unsigned short                  vbIndex,
            const Layout&                   layout,
            unsigned int                    startingAttribIndex = 0,
            unsigned short                  vaIndex = 0
        );
    };

    template<AllocType allocType>
    VertexArray<allocType>::VertexArray(unsigned short count, unsigned int* buf):
        OpenGLBase<allocType>(count, buf)
    {
        GL_CALL(glGenVertexArrays(this->count, this->id));
    }

    template<AllocType allocType>
    VertexArray<allocType>::~VertexArray(){
        GL_CALL(glDeleteVertexArrays(this->count, this->id));
    }

    template<AllocType allocType>
    inline void VertexArray<allocType>::bind(unsigned short index) const{
        GL_CALL(glBindVertexArray(this->id[index]));
    }

    template<AllocType allocType>
    inline void VertexArray<allocType>::unbind() const{
        GL_CALL(glBindVertexArray(0));
    }

    template<AllocType allocType>
    template<typename T, AllocType _allocType>
    void VertexArray<allocType>::readBufferData(
        const VertexBuffer<_allocType>& vb,
        unsigned short                  vbIndex,
        const Layout&                   layout,
        unsigned int                    startingAttribIndex,
        unsigned short                  vaIndex
    ){
        bind(vaIndex);
        vb.bind(vaIndex);

        unsigned int stride = 0;
        for(unsigned int i = 0; i < layout.count; i++)
            stride += (unsigned int)(layout.elements[i].dimension);
        stride *= sizeof(T);

        unsigned long long offset = 0;
        for(unsigned int i = 0; i < layout.count; i++){
            GL_CALL(glEnableVertexAttribArray(startingAttribIndex));
            glVertexAttribPointer(
                startingAttribIndex,
                layout.elements[i].dimension,
                primitiveTypeToGLType<T>(),
                layout.elements[i].normalized ? GL_TRUE:GL_FALSE,
                stride,
                (const void*)offset);
            offset += (layout.elements[i].dimension)*sizeof(T);
            startingAttribIndex++;
        }

    }

}

#endif