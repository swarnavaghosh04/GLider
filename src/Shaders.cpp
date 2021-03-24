#include "GLider/Shaders.hpp"

namespace gli
{

    Shaders::Shaders() noexcept
    {
        GL_CALL(this->id = glCreateProgram());
    }

    Shaders::~Shaders() noexcept
    {
        GL_CALL(glDeleteProgram(this->id));
    }

    void Shaders::compileString(ShaderType shaderType, const char *sourceCode)
    {

        GL_CALL(unsigned int shader = glCreateShader((unsigned int)shaderType));
        GL_CALL(glShaderSource(shader, 1, &sourceCode, NULL));
        GL_CALL(glCompileShader(shader));

        int res;
        GL_CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &res));
        if (res == GL_FALSE)
        {
            GL_CALL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &res));
            char message[res];
            GL_CALL(glGetShaderInfoLog(shader, res, NULL, message));
            GL_CALL(glDeleteShader(shader));
            throw std::runtime_error(message);
        }
        GL_CALL(glAttachShader(this->id, shader));
        GL_CALL(glDeleteShader(shader));
    }

    void Shaders::compileFile(ShaderType shaderType, const char *sourceFilePath)
    {

        if (
            std::ifstream sourceFile(sourceFilePath, std::ios_base::in);
            sourceFile.is_open())
        {
            std::string line, text;
            while (std::getline(sourceFile, line))
            {
                text += line + '\n';
            }
            compileString(shaderType, text.c_str());
        }
        else
        {
            throw std::runtime_error("Cannot Open Shader Source File");
        }
    }

    void Shaders::link()
    {

        GL_CALL(glLinkProgram(this->id));

        int res;
        GL_CALL(glGetProgramiv(this->id, GL_LINK_STATUS, &res));
        if (res == GL_FALSE)
        {
            GL_CALL(glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &res));
            char message[res];
            GL_CALL(glGetProgramInfoLog(this->id, res, NULL, message));
            throw std::runtime_error(message);
        }
    }

    void Shaders::validate() const
    {

        GL_CALL(glValidateProgram(this->id));

        int res;
        GL_CALL(glGetProgramiv(this->id, GL_VALIDATE_STATUS, &res));
        if (res == GL_FALSE)
        {
            GL_CALL(glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &res));
            char message[res];
            GL_CALL(glGetProgramInfoLog(this->id, res, NULL, message));
            throw std::runtime_error(message);
        }
    }

    unsigned int Shaders::getUniformLocation(const char *name)
    {

        // if(uniformLocCache.find(name) != uniformLocCache.end())
        //     return uniformLocCache[name];

        GL_CALL(int loc = glGetUniformLocation(this->id, name));

        if (loc == -1)
            throw std::runtime_error("Uniform not found");

        // uniformLocCache[name] = loc;
        return loc;
    }

}
