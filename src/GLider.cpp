#include "GLider/GLider.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

namespace gli{
    
    void initialize(GLADloadfunc loader){

        if(!gladLoadGL(loader))
            throw std::runtime_error("GLAD Unable to load OpenGL");
    }

}




