#include "GLider/GLider.hpp"

void gli::initialize(){
    if(!gladLoadGL())
        throw std::runtime_error("GLAD Unable to load OpenGL");
}

void gli::initialize(GLADloadproc loader){
    if(!gladLoadGLLoader(loader))
        throw std::runtime_error("GLAD Unable to load OpenGL");
}
