#ifndef HGL_OPENGL_BASE__H_
#define HGL_OPENGL_BASE__H_

#define HGL_DEBUG

#include "HermyGL/HermyGL_core.hpp"
#include "HermyGL/GLErrorHandling.hpp"

#define HGL_DATA_ALLOC_STACK 0
#define HGL_DATA_ALLOC_HEAP 1

namespace hgl{

    /**
     * @brief Converts privitive datatypes to OpenGL definitions
     * 
     * 
     * @tparam T is the specified primitive type. can only be `char`, `short` or `int` along with their unsigned variants, or `float` or `double`
     * @return OpenGL definition like GL_FLOAT, GL_UNSIGNED_INT, etc. If the input is not valid, a value of 0 is returned
    */
    template<typename T>
    constexpr unsigned int primitiveTypeToGLType(){
        return (
            std::is_same<T, char>()             ? GL_BYTE :
            std::is_same<T, unsigned char>()    ? GL_UNSIGNED_BYTE :
            std::is_same<T, short>()            ? GL_SHORT :
            std::is_same<T, unsigned short>()   ? GL_UNSIGNED_SHORT:
            std::is_same<T, int>()              ? GL_INT :
            std::is_same<T, unsigned int>()     ? GL_UNSIGNED_INT :
            std::is_same<T, float>()            ? GL_FLOAT :
            #if defined(GL_VERSION_4_0) && GL_VERSION_4_0 == 1
            std::is_same<T, double>()           ? GL_DOUBLE :
            #endif
            0
        );
    }

    enum AllocType{
        stack = 0, heap
    };

    template<AllocType allocType = AllocType::heap>
    class HERMYGL_EXPORT OpenGLBase{
    protected:
        unsigned short count;
        unsigned int *id;
    public:
        OpenGLBase(unsigned short count, unsigned int* buf = nullptr);
        virtual ~OpenGLBase();
        OpenGLBase(const OpenGLBase& va) = delete;
        OpenGLBase(const OpenGLBase&& va) = delete;
        void operator= (const OpenGLBase& va) = delete;
        void operator= (const OpenGLBase&& va) = delete;
        virtual void bind(unsigned short index = 0) const = 0;
        virtual void unbind() const = 0;
        const unsigned int& operator[] (unsigned int index) const;
        const unsigned int* getId() const;
    };

    template<AllocType allocType>
    OpenGLBase<allocType>::OpenGLBase(unsigned short count, unsigned int* buf):
        count(count)
    {
        if(buf == nullptr){
            if(allocType == heap)
                id = new unsigned int[count];
            else throw 0;
        }
        else id = buf;
    }

    template<AllocType allocType>
    OpenGLBase<allocType>::~OpenGLBase(){
        if(allocType == AllocType::heap) delete[] id;
    }

    template<AllocType allocType>
    inline const unsigned int& OpenGLBase<allocType>::operator[] (unsigned int index) const
    { return id[index]; }

    template<AllocType allocType>
    inline const unsigned int* OpenGLBase<allocType>::getId() const
    { return id; }

}



#endif