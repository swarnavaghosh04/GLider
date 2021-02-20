#ifndef HGL_SHADERS__H_
#define HGL_SHADERS__H_

#include "HermyGL/OpenGLBase.hpp"

namespace hgl{

    enum ShaderTypes : unsigned int{
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
    public:
        Shaders();
        ~Shaders();
        void bind() const;
        void unbind() const;
    };

}

#endif