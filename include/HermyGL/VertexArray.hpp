#ifndef HGL_VERTEXARRAY__H_
#define HGL_VERTEXARRAY__H_

#include "HermyGL/OpenGLBase.hpp"
#include "HermyGL/OpenGLBuffer.hpp"

namespace hgl{

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
        void draw(DrawType mode, int first, int count) const;
    };

    #define TEMP_INST(T)\
        extern template void HERMYGL_EXPORT VertexArray::readBufferData<T>(\
            const OpenGLBuffer<VertexBuffer>&   vb,\
            const LayoutElement*                layout,\
            unsigned int                        layoutCount,\
            unsigned int                        startingAttribIndex = 0\
        )

    __HGL_InstantiateTemplateTypes(TEMP_INST);

    #undef TEMP_INST

}

#endif