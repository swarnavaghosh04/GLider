#include "HermyGL/GLErrorHandling.hpp"

int hgl::numErrors = 0;

void hgl::checkErrors() noexcept{
    
    hgl::numErrors = 0;
    unsigned int error = glGetError();

    while(error != GL_NO_ERROR){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[OpenGL Error] (%u)\n", error);
        hgl::numErrors++;
        error = glGetError();
        return;
    }

}

