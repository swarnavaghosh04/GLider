#include "HermyGL/Shaders.hpp"

hgl::Shaders::Shaders(){
    GL_CALL(this->id = glCreateProgram());
}

hgl::Shaders::~Shaders(){
    GL_CALL(glDeleteShader(this->id));
}

void hgl::Shaders::bind() const{
    GL_CALL(glUseProgram(this->id));
}

void hgl::Shaders::unbind() const{
    GL_CALL(glUseProgram(0));
}
