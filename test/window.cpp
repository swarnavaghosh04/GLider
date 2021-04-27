// Open a window for t milliseconds
constexpr int t = 2000;

#include "GLider/GLider.hpp"
#include <iostream>
#include <exception>
#include <chrono>
#include <cstdlib>

int main(int argc, char* argv[]){

    float openDuration_ms = 0.f;

    if(argc >= 2) openDuration_ms = std::atof(argv[1]);

    if(openDuration_ms <= 0.f){
        std::printf("Duration required! Please enter the number of milliseconds this program should run\n");
        std::printf("\tExample: window 4000    # Runs for 4 seconds\n");
        return 1;
    }

    try{
        gli::initialize(3,0);
    }catch(const std::exception& ex){
        std::cout << "Initialization Error Occured: " << ex.what() << std::endl;
        return 2;
    }

    try{

        SDL_DisplayMode dm;
        if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
            throw std::runtime_error(SDL_GetError());

        gli::OpenGLWindow win{"TestWindow", int(float(dm.w)*3.f/4.f), int(float(dm.h)*3.f/4.f)};

        auto start = std::chrono::steady_clock::now();

        while(
            std::chrono::duration_cast
                <std::chrono::duration<float, std::milli>>
                    (std::chrono::steady_clock::now() - start).count() < openDuration_ms
        ){
            gli::clear(gli::ColorBufferBit | gli::DepthBufferBit);

            win.swap();
        }

    }catch(const std::exception& ex){
        std::cout << "Exception Occured: " << ex.what() << std::endl;
        return 3;
    }

    gli::quit();

    return 0;
}