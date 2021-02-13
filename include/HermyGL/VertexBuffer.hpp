#ifndef HGL_VERTEXBUFFER__H_
#define HGL_VERTEXBUFFER__H_

#include "HermyGL/OpenGLBase.hpp"
#include "HermyGL/VertexBuffer.hpp"

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

    class HERMYGL_EXPORT VertexBuffer : public OpenGLBase{
    private:
        const LayoutElement *layout;
        unsigned int layoutCount;
        friend class VertexArray;
    public:
        VertexBuffer();
        ~VertexBuffer();
        void bind() const;
        void unbind() const;
        template<typename T>
        void feedData(
            const T* data,
            unsigned int count,
            const LayoutElement* layout,
            unsigned int layoutCount,
            unsigned int usage);
    };

    #define feedData_PARAMS(T)          \
        const T* data,                  \
        unsigned int count,             \
        const LayoutElement* layout,    \
        unsigned int layoutCount,       \
        unsigned int usage

    extern template HERMYGL_EXPORT void VertexBuffer::feedData<char>(feedData_PARAMS(char));
    extern template HERMYGL_EXPORT void VertexBuffer::feedData<short>(feedData_PARAMS(short));
    extern template HERMYGL_EXPORT void VertexBuffer::feedData<int>(feedData_PARAMS(int));
    extern template HERMYGL_EXPORT void VertexBuffer::feedData<long>(feedData_PARAMS(long));
    extern template HERMYGL_EXPORT void VertexBuffer::feedData<float>(feedData_PARAMS(float));
    #ifdef INCORPORATE_DOUBLE
    extern template HERMYGL_EXPORT void VertexBuffer::feedData<double>(feedData_PARAMS(double));
    #endif

    #undef feedData_PARAMS

}



#endif