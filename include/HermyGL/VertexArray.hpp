#ifndef HGL_VERTEXARRAY__H_
#define HGL_VERTEXARRAY__H_

#include "HermyGL/HermyGL_core.hpp"
#include "HermyGL/GLErrorHandling.hpp"

namespace hgl{

    class HERMYGL_EXPORT VertexArray{

    private:

        unsigned int id;
        unsigned int layoutIndex=0;

    public:

        VertexArray();
        ~VertexArray();
        VertexArray(const VertexArray& va) = delete;
        VertexArray(const VertexArray&& va) = delete;
        void operator= (const VertexArray& va) = delete;
        void operator= (const VertexArray&& va) = delete;
        void bind() const;
        void unbind() const;
        inline const unsigned int& getId() const { return id; }
        
    };

}

#endif