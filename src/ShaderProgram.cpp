#include "GLider/ShaderProgram.hpp"
#include <optional>

namespace gli
{
    class Shader{

    private:

        const unsigned int id;

        inline int getShaderParameter(unsigned int param) const{
            int res;
            GL_CALL(glGetShaderiv(id, param, &res));
            return res;
        }
        void getInfoLog (char* buffer, unsigned int size) const{
            GL_CALL(glGetShaderInfoLog(id, size, NULL, buffer));
        }
        void throwErrorMessage() const{
            int messageLength = getShaderParameter(GL_INFO_LOG_LENGTH);
            char message[messageLength];
            getInfoLog(message, messageLength);
            throw std::runtime_error(message);
        }
        void checkIfCompileSuccessful() const{
            if(getShaderParameter(GL_COMPILE_STATUS) == GL_FALSE)
                throwErrorMessage();
        }

    public:

        Shader(ShaderType type, const char* source) noexcept(!GLI_DEBUG):
            id{glCreateShader((unsigned int)type)}
        {
            GL_CALL();
            GL_CALL(glShaderSource(id, 1, &source, NULL));
        }
        ~Shader() noexcept(!GLI_DEBUG){
            GL_CALL(glDeleteShader(id));
        }
        void compile(){
            GL_CALL(glCompileShader(id));
            checkIfCompileSuccessful();
        }
        void attachToProgram(ShaderProgram* p) noexcept(!GLI_DEBUG){
            GL_CALL(glAttachShader(p->getID(), this->id));
        }
    };

    ShaderProgram::ShaderProgram() noexcept(!GLI_DEBUG)
    {
        GL_CALL(this->id = glCreateProgram());
    }

    ShaderProgram::~ShaderProgram() noexcept(!GLI_DEBUG)
    {
        GL_CALL(glDeleteProgram(this->id));
    }

    void ShaderProgram::compileString(ShaderType shaderType, const char *sourceCode)
    {
        Shader shader(shaderType, sourceCode);
        shader.compile();
        shader.attachToProgram(this);
    }

    inline std::string convertFileToString(std::ifstream& file){
        return std::string{
            std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>()
        };
    }

    std::optional<std::string> convertFileToString(const char* filePath){

        std::ifstream file(filePath);
        if( ! file.is_open() ) return std::nullopt;
        std::string str(convertFileToString(file));
        file.close();
        return str;
        
    }

    void ShaderProgram::compileFile(ShaderType shaderType, const char *sourceFilePath){

        std::optional<std::string> sourceCode{convertFileToString(sourceFilePath)};
        if(sourceCode) compileString(shaderType, (*sourceCode).c_str());
        else throw std::runtime_error("Cannot Open Shader Source File");

    }

    void ShaderProgram::throwErrorMessage() const{
        int messageLength = getParameter(InfoLogLength);
        char message[messageLength];
        getInfoLog(message, messageLength);
        throw std::runtime_error(message);
    }

    void ShaderProgram::link() const{
        GL_CALL(glLinkProgram(this->id));
        if(getParameter(LinkStatus) == GL_FALSE)
            throwErrorMessage();
    }

    void ShaderProgram::validate() const{
        GL_CALL(glValidateProgram(this->id));
        if(getParameter(ValidateStatus) == GL_FALSE)
            throwErrorMessage();
    }

    unsigned int ShaderProgram::getUniformLocation(const char *name) const{
        GL_CALL(int loc = glGetUniformLocation(this->id, name));
        if (loc == -1)
            throw std::runtime_error("Uniform not found");
        return loc;
    }

}
