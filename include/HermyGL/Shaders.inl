#ifndef HGL_SHADERS__I_
#define HGL_SHADERS__I_

#include "HermyGL/Shaders.hpp"

namespace hgl{

    inline void Shaders::bind() const{
        GL_CALL(glUseProgram(this->id));
    }

    inline void Shaders::use() const{
        bind();
    }

    inline void Shaders::unbind() const{
        GL_CALL(glUseProgram(0));
    }

    #ifdef INCORPORATE_DOUBLE
        #define SET_PROGRAM_UNIFORM_DOUBLE(n, ...)\
            else if(std::is_same<T, double>()) glProgramUniform##n##d(this->id, getUniformLocation(name), __VA_ARGS__);
    #else
        #define SET_PROGRAM_UNIFORM_DOUBLE(n)
    #endif

    #define SET_PROGRAM_UNIFORM(n, ...)\
        if(std::is_same<T, int>()) glProgramUniform##n##i(this->id, getUniformLocation(name), __VA_ARGS__);\
        else if(std::is_same<T, unsigned int>()) glProgramUniform##n##ui(this->id, getUniformLocation(name), __VA_ARGS__);\
        else if(std::is_same<T, float>()) glProgramUniform##n##f(this->id, getUniformLocation(name), __VA_ARGS__);\
        SET_PROGRAM_UNIFORM_DOUBLE(n, __VA_ARGS__)

    template<int L, typename T, glm::qualifier Q>
    void Shaders::setUniform(const char* name, const glm::vec<L,T,Q>& v){

        switch(L){
        case 1:
            SET_PROGRAM_UNIFORM(1, v[0]);
            break;
        case 2:
            SET_PROGRAM_UNIFORM(2, v[0], v[1]);
            break;
        case 3:
            SET_PROGRAM_UNIFORM(3, v[0], v[1], v[2]);
            break;
        case 4:
            SET_PROGRAM_UNIFORM(4, v[0], v[1], v[2], v[3]);
            break;
        default:
            throw std::logic_error("Invalid datatype for uniform");
        }
        
    }

    #undef SET_PROGRAM_UNIFORM
    #undef SET_PROGRAM_UNIFORM_DOUBLE

}
#endif