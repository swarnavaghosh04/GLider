#include "HermyGL/Shaders.hpp"

namespace hgl{

    Shaders::Shaders(){
        GL_CALL(this->id = glCreateProgram());
    }

    Shaders::~Shaders(){
        GL_CALL(glDeleteProgram(this->id));
    }

    void Shaders::bind() const{
        GL_CALL(glUseProgram(this->id));
    }

    void Shaders::use() const{
        bind();
    }

    void Shaders::unbind() const{
        GL_CALL(glUseProgram(0));
    }

    void Shaders::compileString(ShaderTypes shaderType, const char* sourceCode){

        GL_CALL(unsigned int shader = glCreateShader((unsigned int)shaderType));
        GL_CALL(glShaderSource(shader, 1, &sourceCode, NULL));
        GL_CALL(glCompileShader(shader));

        int res;
        GL_CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &res));
        if(res == GL_FALSE){
            GL_CALL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &res));
            char message[res];
            GL_CALL(glGetShaderInfoLog(shader, res, NULL, message));
            GL_CALL(glDeleteShader(shader));
            throw std::runtime_error(message);
        }
        GL_CALL(glAttachShader(this->id, shader));
        GL_CALL(glDeleteShader(shader));

    }

    void Shaders::compileFile(ShaderTypes shaderType, const char* sourceFilePath){

        if(
            std::ifstream sourceFile(sourceFilePath, std::ios_base::in);
            sourceFile.is_open()
        ){
            std::string line, text;
            while(std::getline(sourceFile, line)){
                text += line + '\n';
            }
            compileString(shaderType, text.c_str());
        }else{
            throw std::runtime_error("Cannot Open Shader Source File");
        }

    }

    void Shaders::link(){

        GL_CALL(glLinkProgram(this->id));

        int res;
        GL_CALL(glGetProgramiv(this->id, GL_LINK_STATUS, &res));
        if(res == GL_FALSE){
            GL_CALL(glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &res));
            char message[res];
            GL_CALL(glGetProgramInfoLog(this->id, res, NULL, message));
            throw std::runtime_error(message);
        }
    }

    void Shaders::validate() const{

        GL_CALL(glValidateProgram(this->id));

        int res;
        GL_CALL(glGetProgramiv(this->id, GL_VALIDATE_STATUS, &res));
        if(res == GL_FALSE){
            GL_CALL(glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &res));
            char message[res];
            GL_CALL(glGetProgramInfoLog(this->id, res, NULL, message));
            throw std::runtime_error(message);
        }

    }

    unsigned int Shaders::getUniformLocation(const char* name){

        if(uniformLocCache.find(name) != uniformLocCache.end())
            return uniformLocCache[name];

        GL_CALL(int loc = glGetUniformLocation(this->id, name));

        if(loc == -1)
            throw std::runtime_error("Uniform not found");

        uniformLocCache[name] = loc;
        return loc;
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

    template<typename T>
    void Shaders::setUniform(const char* name, Dimensions dimension, T ...){
        std::va_list args;
        va_start(args, dimension);
        T argList[dimension];
        for(int i = 0; i < dimension; i++) argList[i] = (T)va_arg(args, T);
        va_end(args);
        switch(dimension){
        case Dim_ONE:
            SET_PROGRAM_UNIFORM(1, argList[0]);
            break;
        case Dim_TWO:
            SET_PROGRAM_UNIFORM(2, argList[0], argList[1]);
            break;
        case Dim_THREE:
            SET_PROGRAM_UNIFORM(3, argList[0], argList[1], argList[2]);
            break;
        case Dim_FOUR:
            SET_PROGRAM_UNIFORM(4, argList[0], argList[1], argList[2], argList[3]);
            break;
        }
    }

    #undef SET_PROGRAM_UNIFORM
    #undef SET_PROGRAM_UNIFORM_DOUBLE

    template void Shaders::setUniform<int>(const char* name, Dimensions dimension, int ...);
    template void Shaders::setUniform<unsigned int>(const char* name, Dimensions dimension, unsigned int ...);
    template void Shaders::setUniform<float>(const char* name, Dimensions dimension, float ...);
    #ifdef INCORPORATE_DOUBLE
    template void Shaders::setUniform<double>(const char* name, Dimensions dimension, double ...);
    #endif
}
