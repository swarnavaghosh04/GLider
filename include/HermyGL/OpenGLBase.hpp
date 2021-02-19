#ifndef HGL_OPENGL_BASE__H_
#define HGL_OPENGL_BASE__H_

#include "HermyGL/HermyGL_core.hpp"
#include "HermyGL/GLErrorHandling.hpp"

#define HGL_DATA_ALLOC_STACK 0
#define HGL_DATA_ALLOC_HEAP 1

#if GL_VERSION_4_0
    #define INCORPORATE_DOUBLE
#endif

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
            #ifdef INCORPORATE_DOUBLE
            std::is_same<T, double>()           ? GL_DOUBLE :
            #endif
            0
        );
    }

    #ifdef INCORPORATE_DOUBLE
        #define __HGL_InstantiateTemplateDouble(declarationMacro, ...)\
            declarationMacro(double, ## __VA_ARGS__);
    #else
        #define __HGL_InstantiateTemplateDouble(declarationMacro, ...)
    #endif

    #define __HGL_InstantiateTemplateTypes(declarationMacro, ...)\
        declarationMacro(char              ,## __VA_ARGS__);\
        declarationMacro(unsigned char     ,## __VA_ARGS__);\
        declarationMacro(short             ,## __VA_ARGS__);\
        declarationMacro(unsigned short    ,## __VA_ARGS__);\
        declarationMacro(int               ,## __VA_ARGS__);\
        declarationMacro(unsigned int      ,## __VA_ARGS__);\
        declarationMacro(float             ,## __VA_ARGS__);\
        __HGL_InstantiateTemplateDouble(declarationMacro, ##__VA_ARGS__)
        
    class HERMYGL_EXPORT OpenGLBase{
    protected:
        unsigned int id;
    public:
        OpenGLBase() = default;
        virtual ~OpenGLBase();
        OpenGLBase(const OpenGLBase& va) = delete;
        OpenGLBase(const OpenGLBase&& va) = delete;
        void operator= (const OpenGLBase& va) = delete;
        void operator= (const OpenGLBase&& va) = delete;
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        const unsigned int& getId() const;
    };

}

#endif