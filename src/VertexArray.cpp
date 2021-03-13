#include "HermyGL/VertexArray.hpp"

namespace hgl
{
    VertexArray::VertexArray() noexcept
    {
        GL_CALL(glGenVertexArrays(1, &(this->id)));
    }

    VertexArray::~VertexArray() noexcept
    {
        GL_CALL(glDeleteVertexArrays(1, &(this->id)));
    }

    void VertexArray::draw(DrawType mode, int first, int count) const noexcept
    {
        GL_CALL(glDrawArrays(static_cast<unsigned int>(mode), first, count));
    }
}