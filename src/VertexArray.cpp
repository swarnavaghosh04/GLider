#include "HermyGL/VertexArray.hpp"

namespace hgl{
    VertexArray::VertexArray(){
        GL_CALL(glGenVertexArrays(1, &(this->id)));
    }

    VertexArray::~VertexArray(){
        GL_CALL(glDeleteVertexArrays(1, &(this->id)));
    }

    void VertexArray::draw(DrawType mode, int first, int count) const{
        GL_CALL(glDrawArrays((unsigned int)mode, first, count));
    }
}