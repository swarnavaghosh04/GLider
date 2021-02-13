
/*========================TODO========================

Make a base class for opengl classes like
{
private:
    unsigned int id[n];
public:
    bind();
    unbind();
    operator[]
    getId();
}

=====================================================*/

#ifndef HERMYGL__H_
#define HERMYGL__H_

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include "HermyGL/HermyGL_core.hpp"
#include "HermyGL/Window.hpp"
#include "HermyGL/VertexBuffer.hpp"
#include "HermyGL/VertexArray.hpp"

namespace hgl{

    HERMYGL_EXPORT error initialize();
    HERMYGL_EXPORT void quit();

}

#endif