#include "HermyGL/HermyGL.hpp"

const char* const hgl::noError = "No Errors";

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

//void (*hgl::delay)(Uint32 ms) = SDL_Delay;

hgl::Window::Window(hgl::error &ret, const char* title, int width, int height, Uint32 windowFlags, Uint32 rendererFlags){

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height,
        windowFlags | SDL_WINDOW_OPENGL);

    if(window == NULL){
        ret = {-1, SDL_GetError()};
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, rendererFlags);
    if(renderer == NULL){
        ret = {-2, SDL_GetError()};
        return;
    }
    
    glContext = SDL_GL_CreateContext(window);
    if(glContext == NULL){
        ret = {-3, SDL_GetError()};
        return;
    }

    if(SDL_GL_SetSwapInterval(0) != 0){
        ret = {-4, SDL_GetError()};
        return;
    }

    if(!gladLoadGL()) {
        ret = {-5, "Glad OpenGL Load Error!"};
        return;
    }

    ret = {0, hgl::noError};

}

hgl::Window::~Window(){

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return;
    
}