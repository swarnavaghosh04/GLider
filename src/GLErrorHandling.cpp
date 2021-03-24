#include "GLider/GLErrorHandling.hpp"

int gli::numErrors = 0;

void gli::checkErrors() noexcept{
    
    gli::numErrors = 0;
    unsigned int error = glGetError();

    while(error != GL_NO_ERROR){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[OpenGL Error] (%u)\n", error);
        gli::numErrors++;
        error = glGetError();
        return;
    }

}

