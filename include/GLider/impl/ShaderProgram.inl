#ifndef GLI_SHADERS__I_
#define GLI_SHADERS__I_

#include "GLider/ShaderProgram.hpp"

namespace gli{

    inline ShaderProgram::ShaderProgram(unsigned int id) noexcept:
        OpenGLBase(id)
    {}

    inline void ShaderProgram::bindID(unsigned int anotherID) noexcept{
        GL_CALL(glUseProgram(anotherID));
    }

    inline unsigned int ShaderProgram::getBoundID() noexcept{
        int r;
        glGetIntegerv(GL_CURRENT_PROGRAM, &r);
        return static_cast<unsigned int>(r);
    }

    #define SET_PROGRAM_UNIFORM(n)\
        if constexpr(std::is_same<T, int>())\
            glProgramUniform##n##iv(this->id, getUniformLocation(name), 1, (T*)(&v[0]));\
        else if constexpr(std::is_same<T, unsigned int>())\
            glProgramUniform##n##uiv(this->id, getUniformLocation(name), 1, (T*)(&v[0]));\
        else if constexpr(std::is_same<T, float>())\
            glProgramUniform##n##fv(this->id, getUniformLocation(name), 1, (T*)(&v[0]));\
        else if constexpr(std::is_same<T, double>())\
            glProgramUniform##n##dv(this->id, getUniformLocation(name), 1, (T*)(&v[0]));\
        else throw std::logic_error("Invalid datatype for uniform");

    #define SET_UNIFORM(n)\
        if constexpr(std::is_same<T, int>())\
            glUniform##n##iv(getUniformLocation(name), 1, (T*)(&v[0]));\
        else if constexpr(std::is_same<T, unsigned int>())\
            glUniform##n##uiv(getUniformLocation(name), 1, (T*)(&v[0]));\
        else if constexpr(std::is_same<T, float>())\
            glUniform##n##fv(getUniformLocation(name), 1, (T*)(&v[0]));\
        else if constexpr(INCORPORATE_DOUBLE && std::is_same<T, double>())\
            glUniform##n##dv(getUniformLocation(name), 1, (T*)(&v[0]));\
        else throw std::logic_error("Invalid datatype for uniform");

    template<int L, OpenGLType T, glm::qualifier Q>
    void ShaderProgram::setUniform(const char* name, const glm::vec<L,T,Q>& v){

        #ifdef GL_VERSION_4_1

        switch(L){
        case 1:
            SET_PROGRAM_UNIFORM(1);
            break;
        case 2:
            SET_PROGRAM_UNIFORM(2);
            break;
        case 3:
            SET_PROGRAM_UNIFORM(3);
            break;
        case 4:
            SET_PROGRAM_UNIFORM(4);
            break;
        default:
            throw std::logic_error("Invalid dimension for uniform");
        }

        GL_CALL();

        #else

        Binder b(*this);

        switch(L){
        case 1:
            SET_UNIFORM(1);
            break;
        case 2:
            SET_UNIFORM(2);
            break;
        case 3:
            SET_UNIFORM(3);
            break;
        case 4:
            SET_UNIFORM(4);
            break;
        default:
            throw std::logic_error("Invalid dimension for uniform");
        }

        GL_CALL();

        #endif
        
    }

    #undef SET_PROGRAM_UNIFORM
    #undef SET_UNIFORM

    #define SET_PROGRAM_UNIFORM_MATRIX_N(N)\
        if constexpr(std::is_same<T, float>())\
            glProgramUniformMatrix##N##fv(this->id, getUniformLocation(name), 1, transpose, (T*)&m[0][0]);\
        else if constexpr(std::is_same<T, double>())\
            glProgramUniformMatrix##N##dv(this->id, getUniformLocation(name), 1, transpose, (T*)&m[0][0]);\
        else throw std::logic_error("Invalid datatype for uniform");
    
    #define SET_PROGRAM_UNIFORM_MATRIX_RC(R,C)\
        if constexpr(std::is_same<T, float>())\
            glProgramUniformMatrix##R##x##C##fv(this->id, getUniformLocation(name), 1, transpose, (T*)&m[0][0]);\
        else if constexpr(std::is_same<T, double>())\
            glProgramUniformMatrix##R##x##C##dv(this->id, getUniformLocation(name), 1, transpose, (T*)&m[0][0]);\
        else throw std::logic_error("Invalid datatype for uniform");
    
    #define SET_UNIFORM_MATRIX_N(N)\
        if constexpr(std::is_same<T, float>())\
            glUniformMatrix##N##fv(getUniformLocation(name), 1, transpose, (T*)&m[0][0]);\
        else if constexpr(INCORPORATE_DOUBLE && std::is_same<T, double>())\
            glUniformMatrix##N##dv(getUniformLocation(name), 1, transpose, (T*)&m[0][0]);\
        else throw std::logic_error("Invalid datatype for uniform");
    
    #define SET_UNIFORM_MATRIX_RC(R,C)\
        if constexpr(std::is_same<T, float>())\
            glUniformMatrix##R##x##C##fv(getUniformLocation(name), 1, transpose, (T*)&m[0][0]);\
        else if constexpr(INCORPORATE_DOUBLE && std::is_same<T, double>())\
            glUniformMatrix##R##x##C##dv(getUniformLocation(name), 1, transpose, (T*)&m[0][0]);\
        else throw std::logic_error("Invalid datatype for uniform");

    template<int R, int C, OpenGLType T, glm::qualifier Q>
    void ShaderProgram::setUniform(const char* name, const glm::mat<R,C,T,Q>& m, bool transpose){
        
        #ifdef GL_VERSION_4_1

        if constexpr(R == C){
            
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
        
        #else

        Binder b(*this);

        if constexpr(R == C){
            
            switch(R){
            case 2:
                SET_UNIFORM_MATRIX_N(2);
                break;
            case 3:
                SET_UNIFORM_MATRIX_N(3);
                break;
            case 4:
                SET_UNIFORM_MATRIX_N(4);
                break;
            }

        }else{
            switch(R){
            case 2:
                switch(C){
                case 3:
                    SET_UNIFORM_MATRIX_RC(2,3);
                    break;
                case 4:
                    SET_UNIFORM_MATRIX_RC(2,4);
                    break;
                }
                break;
            case 3:
                switch(C){
                case 2:
                    SET_UNIFORM_MATRIX_RC(3,2);
                    break;
                case 4:
                    SET_UNIFORM_MATRIX_RC(3,4);
                    break;
                }
                break;
            case 4:
                switch(C){
                case 2:
                    SET_UNIFORM_MATRIX_RC(4,2);
                    break;
                case 3:
                    SET_UNIFORM_MATRIX_RC(4,3);
                    break;
                }
                break;
            }
        }

        GL_CALL();

        #endif

    }

    #undef SET_PROGRAM_UNIFORM_MATRIX_N
    #undef SET_PROGRAM_UNIFORM_MATRIX_RC
    #undef SET_UNIFORM_MATRIX_N
    #undef SET_UNIFORM_MATRIX_RC

    inline void ShaderProgram::bindAttribLocation(unsigned int index, const char* name) const noexcept{
        GL_CALL(glBindAttribLocation(this->id, index, name));
    }

    inline int ShaderProgram::getParameter(ProgramParameter param) const noexcept{
        int res;
        GL_CALL(glGetProgramiv(this->id, static_cast<unsigned int>(param), &res));
        return res;
    }

    inline void ShaderProgram::getInfoLog(char* buffer, unsigned int size) const{
        GL_CALL(glGetProgramInfoLog(this->id, size, NULL, buffer));
    }

}
#endif