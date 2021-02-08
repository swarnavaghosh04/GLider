#include "HermyGL/HermyGL.hpp"

hgl::error hgl::initialize(){

    hgl::error ret = {SDL_Init(SDL_INIT_EVERYTHING), hgl::noError};
    if(ret.code < 0){
        ret.message = SDL_GetError();
        return ret;
    }

    ret.code = -1;

    auto checkError = [&](int funcReturn){
        if(funcReturn != 0) throw 0;
        else ret.code--;
    };

    try{
    
        checkError(SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE));
        checkError(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4));
        checkError(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6));
        checkError(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1));
        checkError(SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32));
        checkError(SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1));
        checkError(SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4));
        checkError(SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1));
    
    }catch(...){
        ret.message = SDL_GetError();
        return ret;
    }

    return {0, hgl::noError};
}

void hgl::quit(){
    SDL_Quit();
}

