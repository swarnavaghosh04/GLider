
#include <cstdio>
#include <stdexcept>
#include <utility>

#include "GLider/GLider.hpp"
#include "util.hpp"

void printInfo(){
    std::printf("OpenGL GLAD verision   : %d.%d\n", GLVersion.major, GLVersion.minor);
    std::printf("OpenGL Version         : %s \n", glGetString(GL_VERSION));
    std::printf("OpenGL Shading Version : %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    std::printf("OpenGL Vendor          : %s \n", glGetString(GL_VENDOR));
    std::printf("OpenGL Renderer        : %s \n", glGetString(GL_RENDERER));
}

bool testVersion(std::pair<int,int> version){

    std::printf("\n");

    SDL sdl(version.first, version.second);

    bool working;
    {
        SDL::OpenGLWindow win("Test Window", 100, 100);
        gli::initialize(SDL_GL_GetProcAddress);
        working = GLVersion.major == version.first && GLVersion.minor == version.second;
        if(working){
            printInfo();
            gli::clear(gli::ColorBufferBit);
            win.swap();
        }
    }
    return working;
}

std::pair<int,int> findMaxOpenGLVersion(){

    std::pair<int,int> versions[] = {
        {3,0},
        {3,1},
        {3,2},
        {3,3},
        {4,0},
        {4,1},
        {4,2},
        {4,3},
        {4,4},
        {4,5},
        {4,6},
    };

    int count = sizeof(versions) / sizeof(versions[0]);

    bool versionWorking = testVersion(versions[0]);
    if(!versionWorking) return {0,0};

    for(int i = 1; i < count; i++){
        versionWorking = testVersion(versions[i]);
        if(!versionWorking) return versions[i-1];
    }

    return versions[count-1];

}

int main(int argc, char* argv[]){

    (void)argc;
    (void)argv[0];

    try{

        std::pair<int,int> maxVersion = findMaxOpenGLVersion();

        std::printf("\nThe maximum OpenGL version supported by this device is %d.%d\n\n", maxVersion.first, maxVersion.second);

    }catch(const std::exception& ex){
        std::printf("\nException Occured: %s\n", ex.what());
        return 1;
    }

    return 0;
}