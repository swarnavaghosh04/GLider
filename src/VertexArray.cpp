#include "HermyGL/VertexArray.hpp"

namespace hgl{
    VertexArray::VertexArray() noexcept(true){
        GL_CALL(glGenVertexArrays(1, &(this->id)));
    }

    VertexArray::~VertexArray() noexcept(true){
        GL_CALL(glDeleteVertexArrays(1, &(this->id)));
    }

    void VertexArray::draw(DrawType mode, int first, int count) const noexcept(true){
        GL_CALL(glDrawArrays(static_cast<unsigned int>(mode), first, count));
    }
}