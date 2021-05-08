#ifndef GLI_WINDOW__I_
#define GLI_WINDOW__I_

#include "GLider/Window.hpp"

namespace gli{

    inline void OpenGLWindow::swap() noexcept{
        SDL_GL_SwapWindow(this->window);
    }

}


#endif