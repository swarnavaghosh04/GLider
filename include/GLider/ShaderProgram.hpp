#ifndef GLI_SHADERS__H_
#define GLI_SHADERS__H_

#include <fstream>
#include <cstdarg>
#include <string>
#include "GLider/OpenGLBase.hpp"

namespace gli{

    enum ShaderType : unsigned int{
        #if GL_VERSION_2_0
        VertexShader            = GL_VERTEX_SHADER,
        FragmentShader          = GL_FRAGMENT_SHADER,
        #if GL_VERSION_3_2
        GeometryShader          = GL_GEOMETRY_SHADER,
        #if GL_VERSION_4_0
        TessControlShader       = GL_TESS_CONTROL_SHADER,
        TessEvaluationShader    = GL_TESS_EVALUATION_SHADER,
        #if GL_VERSION_4_3
        ComputeShader           = GL_COMPUTE_SHADER,
        #endif
        #endif
        #endif
        #endif
    };

    enum ProgramParameter : unsigned int{
        DeleteStatus = GL_DELETE_STATUS,
        LinkStatus = GL_LINK_STATUS,
        ValidateStatus = GL_VALIDATE_STATUS,
        InfoLogLength = GL_INFO_LOG_LENGTH,
        AttachedShaders = GL_ATTACHED_SHADERS,
        ActiveAttributes = GL_ACTIVE_ATTRIBUTES,
        ActiveAttributeMaxLength = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
        ActiveUniforms = GL_ACTIVE_UNIFORMS,
        ActiveUniformMaxLength = GL_ACTIVE_UNIFORM_MAX_LENGTH,
        TransformFeedbackBufferMode = GL_TRANSFORM_FEEDBACK_BUFFER_MODE,
        TransformFeedbackVaryings = GL_TRANSFORM_FEEDBACK_VARYINGS,
        TransformFeedbackVaryingMaxLength = GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH,
        #if GL_VERSION_3_1
        ActiveUniformBlocks = GL_ACTIVE_UNIFORM_BLOCKS,
        ActiveUniformBlockMaxNameLength = GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH,
        #if GL_VERSION_3_2
        GeometryVerticesOut = GL_GEOMETRY_VERTICES_OUT,
        GeometryInputType = GL_GEOMETRY_INPUT_TYPE,
        GeometryOutputType = GL_GEOMETRY_OUTPUT_TYPE,
        #if GL_VERSION_4_2
        ActiveAtomicCounterBuffers = GL_ACTIVE_ATOMIC_COUNTER_BUFFERS,
        ProgramBinaryLength = GL_PROGRAM_BINARY_LENGTH,
        #if GL_VERSION_4_3
        ComputeWorkGroupSize = GL_COMPUTE_WORK_GROUP_SIZE,
        #endif
        #endif
        #endif
        #endif
    };

    class ShaderProgram : public OpenGLBase<ShaderProgram>{
    private:
        friend class OpenGLBase<ShaderProgram>;
        ShaderProgram(unsigned int id) noexcept;
        static void bindID(unsigned int id) noexcept;
        static unsigned int getBoundID() noexcept;
        void getInfoLog(char* buffer, unsigned int size) const;
        void throwErrorMessage() const;
    public:
        ShaderProgram() noexcept;
        ~ShaderProgram() noexcept;
        void compileString(ShaderType shaderType, const char* sourceCode);
        void compileFile(ShaderType shaderType, const char* sourceFilePath);
        void link() const;
        void validate() const;
        int getParameter(ProgramParameter param) const noexcept;
        unsigned int getUniformLocation(const char* name) const;
        template<int L, OpenGLType T, glm::qualifier Q>
        void setUniform(const char* name, const glm::vec<L,T,Q>& v);
        template<int R, int C, OpenGLType T, glm::qualifier Q>
        void setUniform(const char* name, const glm::mat<R,C,T,Q>& m, bool transpose);
        void bindAttribLocation(unsigned int index, const char* name) const noexcept;
    };

}

#include "GLider/impl/ShaderProgram.inl"

#endif