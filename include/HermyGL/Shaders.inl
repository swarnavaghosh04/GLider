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
        SET_PROGRAM_UNIFORM_DOUBLE(n, __VA_ARGS__)\
        else throw std::logic_error("Invalid datatype for uniform");

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
            throw std::logic_error("Invalid dimension for uniform");
        }
        
    }

    #undef SET_PROGRAM_UNIFORM
    #undef SET_PROGRAM_UNIFORM_DOUBLE

    #ifdef INCORPORATE_DOUBLE
        #define SET_PROGRAM_UNIFORM_MATRIX_N_DOUBLE(n)\
            else if(std::is_same<T, double>()) glProgramUniformMatrix##n##dv(this->id, getUniformLocation(name), 1, transpose, (double*)&m[0][0]);
        #define SET_PROGRAM_UNIFORM_MATRIX_RC_DOUBLE(R,C)\
            else if(std::is_same<T, double>()) glProgramUniformMatrix##R##x##C##dv(this->id, getUniformLocation(name), 1, transpose, (double*)&m[0][0]);
    #else
        #define SET_PROGRAM_UNIFORM_MATRIX__NDOUBLE(n)
    #endif

    #define SET_PROGRAM_UNIFORM_MATRIX_N(n)\
        if(std::is_same<T, float>()) glProgramUniformMatrix##n##fv(this->id, getUniformLocation(name), 1, transpose, (float*)&m[0][0]);\
        SET_PROGRAM_UNIFORM_MATRIX_N_DOUBLE(n)\
        else throw std::logic_error("Invalid datatype for uniform");

    #define SET_PROGRAM_UNIFORM_MATRIX_RC(R,C)\
        if(std::is_same<T, float>()) glProgramUniformMatrix##R##x##C##fv(this->id, getUniformLocation(name), 1, transpose, (float*)&m[0][0]);\
        SET_PROGRAM_UNIFORM_MATRIX_RC_DOUBLE(R,C)\
        else throw std::logic_error("Invalid datatype for uniform");

    template<int R, int C, typename T, glm::qualifier Q>
    void Shaders::setUniform(const char* name, const glm::mat<R,C,T,Q>& m, bool transpose){

        if(R == C){
            
            switch(R){
            case 2:
                SET_PROGRAM_UNIFORM_MATRIX_N(2);
                break;
            case 3:
                SET_PROGRAM_UNIFORM_MATRIX_N(3);
                break;
            case 4:
                SET_PROGRAM_UNIFORM_MATRIX_N(4);
                break;
            }

        }else{
            switch(R){
            case 2:
                switch(C){
                case 3:
                    SET_PROGRAM_UNIFORM_MATRIX_RC(2,3);
                    break;
                case 4:
                    SET_PROGRAM_UNIFORM_MATRIX_RC(2,4);
                    break;
                }
                break;
            case 3:
                switch(C){
                case 2:
                    SET_PROGRAM_UNIFORM_MATRIX_RC(3,2);
                    break;
                case 4:
                    SET_PROGRAM_UNIFORM_MATRIX_RC(3,4);
                    break;
                }
                break;
            case 4:
                switch(C){
                case 2:
                    SET_PROGRAM_UNIFORM_MATRIX_RC(4,2);
                    break;
                case 3:
                    SET_PROGRAM_UNIFORM_MATRIX_RC(4,3);
                    break;
                }
                break;
            }
        }

    }

    #undef SET_PROGRAM_UNIFORM_MATRIX_N
    #undef SET_PROGRAM_UNIFORM_MATRIX_N_DOUBLE
    #undef SET_PROGRAM_UNIFORM_MATRIX_RC
    #undef SET_PROGRAM_UNIFORM_MATRIX_RC_DOUBLE

}
#endif