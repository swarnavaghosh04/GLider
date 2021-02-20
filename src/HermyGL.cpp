#include "HermyGL/HermyGL.hpp"

void hgl::initialize(){

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw std::runtime_error(SDL_GetError());

    int errorVal = 0;
    
    errorVal += SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    errorVal += SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    errorVal += SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    errorVal += SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    errorVal += SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    errorVal += SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    errorVal += SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    errorVal += SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    if(errorVal < 0){
        SDL_Quit();
        throw std::runtime_error(SDL_GetError());
    }

}

void hgl::quit(){
    SDL_Quit();
}

