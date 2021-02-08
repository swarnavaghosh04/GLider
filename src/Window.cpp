#include "HermyGL/Window.hpp"

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