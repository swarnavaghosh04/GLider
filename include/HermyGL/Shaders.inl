#ifndef HGL_SHADERS__I_
#define HGL_SHADERS__I_

#include "HermyGL/Shaders.hpp"

namespace hgl{

    inline void Shaders::bind() const noexcept{
        GL_CALL(glUseProgram(this->id));
    }

    inline void Shaders::staticBind(unsigned int anotherID) noexcept{
        GL_CALL(glUseProgram(anotherID));
    }

    inline void Shaders::staticUnbind() noexcept{
        GL_CALL(glUseProgram(0));
    }

    inline int Shaders::staticGetBound() noexcept{
        int r;
        glGetIntegerv(GL_CURRENT_PROGRAM, &r);
        return r;
    }

    #ifdef INCORPORATE_DOUBLE
        #define SET_PROGRAM_UNIFORM_DOUBLE(n, ...)\
            else if(std::is_same<T, double>()) glUniform##n##d(getUniformLocation(name), __VA_ARGS__);
    #else
        #define SET_PROGRAM_UNIFORM_DOUBLE(n)
    #endif

    #define SET_PROGRAM_UNIFORM(n, ...)\
        if(std::is_same<T, int>()) glUniform##n##i(getUniformLocation(name), __VA_ARGS__);\
        else if(std::is_same<T, unsigned int>()) glUniform##n##ui(getUniformLocation(name), __VA_ARGS__);\
        else if(std::is_same<T, float>()) glUniform##n##f(getUniformLocation(name), __VA_ARGS__);\
        SET_PROGRAM_UNIFORM_DOUBLE(n, __VA_ARGS__)\
        else throw std::logic_error("Invalid datatype for uniform");

    template<int L, typename T, glm::qualifier Q>
    void Shaders::setUniform(const char* name, const glm::vec<L,T,Q>& v){

        Binder b(*this);

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

        GL_CALL();
        
    }

    #undef SET_PROGRAM_UNIFORM
    #undef SET_PROGRAM_UNIFORM_DOUBLE

    #ifdef INCORPORATE_DOUBLE
        #define SET_PROGRAM_UNIFORM_MATRIX_N_DOUBLE(n)\
            else if(std::is_same<T, double>()) glUniformMatrix##n##dv(getUniformLocation(name), 1, transpose, (double*)&m[0][0]);
        #define SET_PROGRAM_UNIFORM_MATRIX_RC_DOUBLE(R,C)\
            else if(std::is_same<T, double>()) glUniformMatrix##R##x##C##dv(getUniformLocation(name), 1, transpose, (double*)&m[0][0]);
    #else
        #define SET_PROGRAM_UNIFORM_MATRIX_N_DOUBLE(n)
        #define SET_PROGRAM_UNIFORM_MATRIX_RC_DOUBLE(R,C)
    #endif

    #define SET_PROGRAM_UNIFORM_MATRIX_N(n)\
        if(std::is_same<T, float>()) glUniformMatrix##n##fv(getUniformLocation(name), 1, transpose, (float*)&m[0][0]);\
        SET_PROGRAM_UNIFORM_MATRIX_N_DOUBLE(n)\
        else throw std::logic_error("Invalid datatype for uniform");

    #define SET_PROGRAM_UNIFORM_MATRIX_RC(R,C)\
        if(std::is_same<T, float>()) glUniformMatrix##R##x##C##fv(getUniformLocation(name), 1, transpose, (float*)&m[0][0]);\
        SET_PROGRAM_UNIFORM_MATRIX_RC_DOUBLE(R,C)\
        else throw std::logic_error("Invalid datatype for uniform");

    template<int R, int C, typename T, glm::qualifier Q>
    void Shaders::setUniform(const char* name, const glm::mat<R,C,T,Q>& m, bool transpose){

        Binder b(*this);

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

        GL_CALL();

    }

    #undef SET_PROGRAM_UNIFORM_MATRIX_N
    #undef SET_PROGRAM_UNIFORM_MATRIX_N_DOUBLE
    #undef SET_PROGRAM_UNIFORM_MATRIX_RC
    #undef SET_PROGRAM_UNIFORM_MATRIX_RC_DOUBLE

}
#endif