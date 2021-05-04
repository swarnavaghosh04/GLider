#include "GLider/GLider.hpp"

void gli::checkVersion(int major, int minor){

    #if !GL_VERSION_3_0
        static_assert(false, "GLAD must load AT LEAST OpenGL 3.0");
    #endif

    switch(major){
    case 3:
        if(minor < 0 || minor > 3)
            throw std::invalid_argument("Invalid minor version for OpenGL 3.x inputted for initialization");
        break;
    case 4:
        if(minor < 0 || minor > 6)
            throw std::invalid_argument("Invalid minor version for OpenGL 4.x inputted for initialization");
        break;
    default:
        throw std::invalid_argument("OpenGL major version inputted for initialization should be either 3 or 4");
    }
}

void gli::initialize_base(int major, int minor, const std::function<void(int&)>& attributeSetter){

    #ifdef GLI_DEBUG
        SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG);
    #endif

    checkVersion(major, minor);

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw std::runtime_error(SDL_GetError());

    int errorVal = 0;

    attributeSetter(errorVal);
    
    errorVal += SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    errorVal += SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
    errorVal += SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);

    if(errorVal < 0){
        SDL_Quit();
        throw std::runtime_error(SDL_GetError());
    }

}

template<typename T>
void gli::initialize(int major, int minor, const T& attributes){

    initialize_base(major,minor, [&](int& errorVal){
        for(const std::pair<SDL_GLattr, int>& p : attributes)
            errorVal += SDL_GL_SetAttribute(p.first, p.second);
    });

    SDL_Log("Hellooo!");
}

template void gli::initialize(int major, int minor, const SDLAttributeList& attributes);
template void gli::initialize(int major, int minor, const SDLAttributeVector& attributes);


void gli::quit() noexcept{
    SDL_Quit();
}

