#ifndef HGL_SHADERS__H_
#define HGL_SHADERS__H_

#include <fstream>
#include <unordered_map>
#include <cstdarg>
#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    enum ShaderType : unsigned int{
        #if GL_VERSION_2_0
        VertexShader            = GL_VERTEX_SHADER,
        FragmentShader          = GL_FRAGMENT_SHADER,
        #endif
        #if GL_VERSION_3_0
        GeometryShader          = GL_GEOMETRY_SHADER,
        #endif
        #if GL_VERSION_4_0
        TessControlShader       = GL_TESS_CONTROL_SHADER,
        TessEvaluationShader    = GL_TESS_EVALUATION_SHADER,
        #endif
        #if GL_VERSION_4_3
        ComputeShader           = GL_COMPUTE_SHADER,
        #endif
    };

    class HERMYGL_EXPORT Shaders : public OpenGLBase{
    private:
        std::unordered_map<const char*, unsigned int> uniformLocCache;
    public:
        Shaders();
        ~Shaders();
        void bind() const;
        void unbind() const;
        void use() const;
        void compileString(ShaderType shaderType, const char* sourceCode);
        void compileFile(ShaderType shaderType, const char* sourceFilePath);
        void link();
        void validate() const;
        unsigned int getUniformLocation(const char* name);
        template<int L, typename T, glm::qualifier Q>
        void setUniform(const char* name, const glm::vec<L,T,Q>& v);
        template<int R, int C, typename T, glm::qualifier Q>
        void setUniform(const char* name, const glm::mat<R,C,T,Q>& m, bool transpose);
    };

}

#include "HermyGL/Shaders.inl"

#endif