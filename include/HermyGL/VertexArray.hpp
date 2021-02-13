#ifndef HGL_VERTEXARRAY__H_
#define HGL_VERTEXARRAY__H_

#include "HermyGL/OpenGLBase.hpp"
#include "HermyGL/VertexBuffer.hpp"

namespace hgl{

    class HERMYGL_EXPORT VertexArray : public OpenGLBase{
    public:
        VertexArray();
        ~VertexArray();
        void bind() const;
        void unbind() const;
        template<typename T>
        void readBufferData(
            const VertexBuffer&     vb,
            unsigned int            startingAttribIndex = 0
        );
    };

    #define readBufferData_PARAMS\
        const VertexBuffer&     vb,                     \
        unsigned int            startingAttribIndex = 0

    extern template HERMYGL_EXPORT void VertexArray::readBufferData<char>(readBufferData_PARAMS);
    extern template HERMYGL_EXPORT void VertexArray::readBufferData<short>(readBufferData_PARAMS);
    extern template HERMYGL_EXPORT void VertexArray::readBufferData<int>(readBufferData_PARAMS);
    extern template HERMYGL_EXPORT void VertexArray::readBufferData<long>(readBufferData_PARAMS);
    extern template HERMYGL_EXPORT void VertexArray::readBufferData<float>(readBufferData_PARAMS);
    #ifdef INCORPORATE_DOUBLE
    extern template HERMYGL_EXPORT void VertexArray::readBufferData<double>(readBufferData_PARAMS);
    #endif

    #undef readBufferData_PARAMS

}

#endif