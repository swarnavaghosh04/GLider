#include "HermyGL/HermyGL.hpp"
#include <iostream>

inline void printError(const char* message, const hgl::error& e){
    SDL_Log("%s: [%d] %s (%d)\n", message, e.code, e.message, (int)(e.message != hgl::noError));
}

int main(int argc, const char* argv[]){

    hgl::error err;

    err = hgl::initialize();
    printError("Initialization", err);

    hgl::Window window = {err, "Test Window", 500, 400, 0, 0};
    printError("Window Creation", err);

    bool keepRunning = true;
    SDL_Event e;

    while(keepRunning){

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                keepRunning = false;
                break;
            }
        }

    }

    hgl::quit();

    return 0;

}