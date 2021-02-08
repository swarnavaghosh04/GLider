#include "HermyGL/VertexArray.hpp"

hgl::VertexArray::VertexArray(){
    GL_CALL(glGenVertexArrays(1, &id));
    GL_CALL(glBindVertexArray(id));
}

hgl::VertexArray::~VertexArray(){
    GL_CALL(glDeleteVertexArrays(1, &id));
}

void hgl::VertexArray::bind() const{
    GL_CALL(glBindVertexArray(id));
}

void hgl::VertexArray::unbind() const{
    GL_CALL(glBindVertexArray(0));
}
