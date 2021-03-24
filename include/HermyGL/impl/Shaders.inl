#ifndef HGL_SHADERS__I_
#define HGL_SHADERS__I_

#include "HermyGL/Shaders.hpp"

namespace hgl{

    inline void Shaders::bind() const noexcept{
        GL_CALL(glUseProgram(this->id));
    }

    inline void Shaders::bind(unsigned int anotherID) noexcept{
        GL_CALL(glUseProgram(anotherID));
    }

    inline void Shaders::unbind() noexcept{
        GL_CALL(glUseProgram(0));
    }

    inline int Shaders::getBound() noexcept{
        int r;
        glGetIntegerv(GL_CURRENT_PROGRAM, &r);
        return r;
    }

    
    #define COMMA ,

    #define SET_PROGRAM_UNIFORM(n, Program, thisID, ...)\
        if(std::is_same<T, int>())\
            gl##Program##Uniform##n##i(thisID getUniformLocation(name), __VA_ARGS__);\
        else if(std::is_same<T, unsigned int>())\
            gl##Program##Uniform##n##ui(thisID getUniformLocation(name), __VA_ARGS__);\
        else if(std::is_same<T, float>())\
            gl##Program##Uniform##n##f(thisID getUniformLocation(name), __VA_ARGS__);\
        else if(std::is_same<T, double>() && GLVersion.major == 4)\
            gl##Program##Uniform##n##d(thisID getUniformLocation(name), __VA_ARGS__);\
        else throw std::logic_error("Invalid datatype for uniform");

    template<int L, typename T, glm::qualifier Q>
    void Shaders::setUniform(const char* name, const glm::vec<L,T,Q>& v){

        if(GLVersion.major == 4 && GLVersion.minor >= 0){

            switch(L){
            case 1:
                SET_PROGRAM_UNIFORM(1, Program, this->id COMMA, v[0]);
                break;
            case 2:
                SET_PROGRAM_UNIFORM(2, Program, this->id COMMA, v[0], v[1]);
                break;
            case 3:
                SET_PROGRAM_UNIFORM(3, Program, this->id COMMA, v[0], v[1], v[2]);
                break;
            case 4:
                SET_PROGRAM_UNIFORM(4, Program, this->id COMMA, v[0], v[1], v[2], v[3]);
                break;
            default:
                throw std::logic_error("Invalid dimension for uniform");
            }

            GL_CALL();

            return;
        }

        
        Binder b(*this);

        switch(L){
        case 1:
            SET_PROGRAM_UNIFORM(1,,, v[0]);
            break;
        case 2:
            SET_PROGRAM_UNIFORM(2,,, v[0], v[1]);
            break;
        case 3:
            SET_PROGRAM_UNIFORM(3,,, v[0], v[1], v[2]);
            break;
        case 4:
            SET_PROGRAM_UNIFORM(4,,, v[0], v[1], v[2], v[3]);
            break;
        default:
            throw std::logic_error("Invalid dimension for uniform");
        }

        GL_CALL();
        
    }

    #undef SET_PROGRAM_UNIFORM

    #define SET_PROGRAM_UNIFORM_MATRIX_N(N, Program, thisID)\
        if(std::is_same<T, float>())\
            gl##Program##UniformMatrix##N##fv(thisID getUniformLocation(name), 1, transpose, (float*)&m[0][0]);\
        else if(std::is_same<T, double>() && GLVersion.major == 4)\
            gl##Program##UniformMatrix##N##dv(thisID getUniformLocation(name), 1, transpose, (double*)&m[0][0]);\
        else throw std::logic_error("Invalid datatype for uniform");

    #define SET_PROGRAM_UNIFORM_MATRIX_RC(R,C,Program, thisID)\
        if(std::is_same<T, float>())\
            gl##Program##UniformMatrix##R##x##C##fv(thisID getUniformLocation(name), 1, transpose, (float*)&m[0][0]);\
        else if(std::is_same<T, double>() && GLVersion.major == 4)\
            gl##Program##UniformMatrix##R##x##C##dv(thisID getUniformLocation(name), 1, transpose, (double*)&m[0][0]);\
        else throw std::logic_error("Invalid datatype for uniform");

    template<int R, int C, typename T, glm::qualifier Q>
    void Shaders::setUniform(const char* name, const glm::mat<R,C,T,Q>& m, bool transpose){

        if(GLVersion.major == 4 && GLVersion.minor >= 0){

            if(R == C){
                
                switch(R){
                case 2:
                    SET_PROGRAM_UNIFORM_MATRIX_N(2,Program, this->id COMMA);
                    break;
                case 3:
                    SET_PROGRAM_UNIFORM_MATRIX_N(3,Program, this->id COMMA);
                    break;
                case 4:
                    SET_PROGRAM_UNIFORM_MATRIX_N(4,Program, this->id COMMA);
                    break;
                }

            }else{
                switch(R){
                case 2:
                    switch(C){
                    case 3:
                        SET_PROGRAM_UNIFORM_MATRIX_RC(2,3,Program, this->id COMMA);
                        break;
                    case 4:
                        SET_PROGRAM_UNIFORM_MATRIX_RC(2,4,Program, this->id COMMA);
                        break;
                    }
                    break;
                case 3:
                    switch(C){
                    case 2:
                        SET_PROGRAM_UNIFORM_MATRIX_RC(3,2,Program, this->id COMMA);
                        break;
                    case 4:
                        SET_PROGRAM_UNIFORM_MATRIX_RC(3,4,Program, this->id COMMA);
                        break;
                    }
                    break;
                case 4:
                    switch(C){
                    case 2:
                        SET_PROGRAM_UNIFORM_MATRIX_RC(4,2,Program, this->id COMMA);
                        break;
                    case 3:
                        SET_PROGRAM_UNIFORM_MATRIX_RC(4,3,Program, this->id COMMA);
                        break;
                    }
                    break;
                }
            }

            GL_CALL();
            return;
        }

        Binder b(*this);

        if(R == C){
            
            switch(R){
            case 2:
                SET_PROGRAM_UNIFORM_MATRIX_N(2,,);
                break;
            case 3:
                SET_PROGRAM_UNIFORM_MATRIX_N(3,,);
                break;
            case 4:
                SET_PROGRAM_UNIFORM_MATRIX_N(4,,);
                break;
            }

        }else{
            switch(R){
            case 2:
                switch(C){
                case 3:
                    SET_PROGRAM_UNIFORM_MATRIX_RC(2,3,,);
                    break;
                case 4:
                    SET_PROGRAM_UNIFORM_MATRIX_RC(2,4,,);
                    break;
                }
                break;
            case 3:
                switch(C){
                case 2:
                    SET_PROGRAM_UNIFORM_MATRIX_RC(3,2,,);
                    break;
                case 4:
                    SET_PROGRAM_UNIFORM_MATRIX_RC(3,4,,);
                    break;
                }
                break;
            case 4:
                switch(C){
                case 2:
                    SET_PROGRAM_UNIFORM_MATRIX_RC(4,2,,);
                    break;
                case 3:
                    SET_PROGRAM_UNIFORM_MATRIX_RC(4,3,,);
                    break;
                }
                break;
            }
        }

        GL_CALL();

    }

    #undef SET_PROGRAM_UNIFORM_MATRIX_N
    #undef SET_PROGRAM_UNIFORM_MATRIX_RC

    #undef COMMA

}
#endif