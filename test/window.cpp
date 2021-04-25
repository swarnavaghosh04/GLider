// Open a window for t milliseconds
constexpr int t = 2000;

#include "GLider/GLider.hpp"
#include <iostream>
#include <exception>
#include <chrono>

int main(){

    try{
        gli::initialize(3,0);
    }catch(const std::exception& ex){
        std::cout << "Initialization Error Occured: " << ex.what() << std::endl;
        return 1;
    }

    try{

        SDL_DisplayMode dm;
        if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
            throw std::runtime_error(SDL_GetError());

        gli::OpenGLWindow win{"TestWindow", int(float(dm.w)*3.f/4.f), int(float(dm.h)*3.f/4.f)};

        auto start = std::chrono::steady_clock::now();

        while(
            std::chrono::duration_cast
                <std::chrono::milliseconds>
                    (std::chrono::steady_clock::now() - start).count() < t
        ){
            gli::clear(gli::ColorBufferBit | gli::DepthBufferBit);

            win.swap();
        }

    }catch(const std::exception& ex){
        std::cout << "Exception Occured: " << ex.what() << std::endl;
        return 2;
    }

    gli::quit();

    return 0;
}