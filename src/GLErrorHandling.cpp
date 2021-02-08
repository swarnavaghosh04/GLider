#include "HermyGL/GLErrorHandling.hpp"

int hgl::numErrors = 0;

void hgl::checkErrors(){
    
    unsigned int error = glGetError();
    hgl::numErrors = 0;

    if(error != GL_NO_ERROR){
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "[OpenGL Error] (%u)\n", error);
        numErrors++;
        return;
    }

}

