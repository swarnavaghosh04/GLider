#ifndef HGL_VERTEXARRAY__H_
#define HGL_VERTEXARRAY__H_

#include "HermyGL/OpenGLBase.hpp"
#include "HermyGL/OpenGLBuffer.hpp"
//#include "HermyGL/VertexBuffer.hpp"

namespace hgl{

    enum Dimensions : unsigned char{
        Dim_ONE = 1, Dim_TWO = 2, Dim_THREE = 3, Dim_FOUR = 4
    };

    enum Normalized : bool{
        Norm_FALSE = false, Norm_TRUE = true
    };

    struct LayoutElement{
        Dimensions dimension;
        Normalized normalized;
    };

    class HERMYGL_EXPORT VertexArray : public OpenGLBase{
    public:
        VertexArray();
        ~VertexArray();
        void bind() const;
        void unbind() const;
        template<typename T>
        void readBufferData(
            const OpenGLBuffer<VertexBuffer>&   vb,
            const LayoutElement*                layout,
            unsigned int                        layoutCount,
            unsigned int                        startingAttribIndex = 0
        );
    };

    #define TEMP_INST(T)\
        extern template void HERMYGL_EXPORT VertexArray::readBufferData<T>(\
            const OpenGLBuffer<VertexBuffer>&   vb,\
            const LayoutElement*                layout,\
            unsigned int                        layoutCount,\
            unsigned int                        startingAttribIndex = 0\
        )

    TEMP_INST(char);
    TEMP_INST(unsigned char);
    TEMP_INST(short);
    TEMP_INST(unsigned short);
    TEMP_INST(int);
    TEMP_INST(unsigned int);
    TEMP_INST(long);
    TEMP_INST(unsigned long);
    TEMP_INST(float);
    #ifdef INCORPORATE_DOUBLE
    TEMP_INST(double);
    #endif

    #undef TEMP_INST

}

#endif