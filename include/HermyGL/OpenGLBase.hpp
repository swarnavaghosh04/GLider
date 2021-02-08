#ifndef HGL_OPENGL_BASE__H_
#define HGL_OPENGL_BASE__H_

#define HGL_DEBUG

#include "HermyGL/HermyGL_core.hpp"
#include "HermyGL/GLErrorHandling.hpp"

#define HGL_DATA_ALLOC_STACK 0
#define HGL_DATA_ALLOC_HEAP 1

namespace hgl{

    enum AllocType{
        stack = 0, heap
    };

    template<AllocType dataAllocType>
    class HERMYGL_EXPORT OpenGLBase{

    protected:
        unsigned short count;
        unsigned int *id;
    public:
        OpenGLBase(unsigned short count);
        virtual ~OpenGLBase();
        OpenGLBase(const OpenGLBase& va) = delete;
        OpenGLBase(const OpenGLBase&& va) = delete;
        void operator= (const OpenGLBase& va) = delete;
        void operator= (const OpenGLBase&& va) = delete;
        virtual void bind(unsigned short index) const = 0;
        virtual void unbind() const = 0;
        inline const unsigned int& operator[] (const unsigned int index) const { return id[index]; }
        inline const unsigned int* getId() const { return id; }
    };

}

#endif