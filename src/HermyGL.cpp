#include "HermyGL/HermyGL.hpp"

hgl::Window::Window(const char* title, int width, int height, Uint32 windowFlags, Uint32 rendererFlags){

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height,
        windowFlags);

}