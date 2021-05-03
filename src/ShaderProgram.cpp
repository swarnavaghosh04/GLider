#include "GLider/ShaderProgram.hpp"

namespace gli
{

    ShaderProgram::ShaderProgram() noexcept
    {
        GL_CALL(this->id = glCreateProgram());
    }

    ShaderProgram::~ShaderProgram() noexcept
    {
        GL_CALL(glDeleteProgram(this->id));
    }

    class Shader{
    private:

        const unsigned int id;

        inline int get(unsigned int value){
            int res;
            GL_CALL(glGetShaderiv(id, value, &res));
            return res;
        }
        void throwErrorMessage(){
            int messageLength = get(GL_INFO_LOG_LENGTH);
            char message[messageLength];
            GL_CALL(glGetShaderInfoLog(id, messageLength, NULL, message));
            throw std::runtime_error(message);
        }
        void checkIfCompileSuccessful(){
            if(get(GL_COMPILE_STATUS) == GL_FALSE)
                throwErrorMessage();
        }
    public:
        Shader(ShaderType type, const char* source) noexcept:
            id{glCreateShader((unsigned int)type)}
        {
            GL_CALL();
            GL_CALL(glShaderSource(id, 1, &source, NULL));
        }
        ~Shader() noexcept{
            GL_CALL(glDeleteShader(id));
        }
        void compile(){
            GL_CALL(glCompileShader(id));
            checkIfCompileSuccessful();
        }
        void attachToProgram(ShaderProgram* p) noexcept{
            GL_CALL(glAttachShader(p->getID(), this->id));
        }
    };

    void ShaderProgram::compileString(ShaderType shaderType, const char *sourceCode)
    {

        Shader shader(shaderType, sourceCode);
        shader.compile();
        shader.attachToProgram(this);

    }

    void ShaderProgram::compileFile(ShaderType shaderType, const char *sourceFilePath)
    {

        if (
            std::ifstream sourceFile(sourceFilePath);
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

    void ShaderProgram::link()
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

    void ShaderProgram::validate() const
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

    unsigned int ShaderProgram::getUniformLocation(const char *name)
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
