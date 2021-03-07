#include "HermyGL/HermyGL.hpp"

void hgl::initialize(int major, int minor){

    static_assert(GL_VERSION_3_0, "Glad should provide at least OpenGL 3.0");

    switch(major){
    case 3:
        if(minor < 0 || minor > 3)
            throw std::runtime_error("Unrecognized OpenGL Version");
        break;
    case 4:
        if(minor < 0 || minor > 6)
            throw std::runtime_error("Unrecognized OpenGL Version");
        break;
    default:
        throw std::runtime_error("Provided major version should be either 3 or 4");
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw std::runtime_error(SDL_GetError());

    int errorVal = 0;
    
    errorVal += SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    errorVal += SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
    errorVal += SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
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

void hgl::quit() noexcept{
    SDL_Quit();
}

