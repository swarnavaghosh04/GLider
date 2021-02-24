#include "HermyGL/Window.hpp"

namespace hgl{

    Window::Window(const char* title, int width, int height, Uint32 windowFlags, Uint32 rendererFlags){

        window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width, height,
            windowFlags | SDL_WINDOW_OPENGL);

        if(window == NULL)
            throw std::runtime_error(SDL_GetError());

        renderer = SDL_CreateRenderer(window, -1, rendererFlags);

        if(renderer == NULL){
            SDL_DestroyWindow(window);
            throw std::runtime_error(SDL_GetError());
        }
        
        glContext = SDL_GL_CreateContext(window);

        if(glContext == NULL){
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            throw std::runtime_error(SDL_GetError());
        }

        if(SDL_GL_SetSwapInterval(0) != 0){
            SDL_GL_DeleteContext(glContext);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            throw std::runtime_error(SDL_GetError());
        }

        if(!gladLoadGL()) {
            SDL_GL_DeleteContext(glContext);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            throw std::runtime_error("GLAD Unable to load OpenGL");
        }

    }

    Window::~Window(){

        SDL_GL_DeleteContext(glContext);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return;
        
    }

}