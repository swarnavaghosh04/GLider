#include "GLider/GLider.hpp"
#include <iostream>
#include <exception>

int main(int argc, const char* argv[]){

    (void)argc;
    (void)argv[0];

    try{
        gli::initialize(3,0);
    }catch(const std::exception& ex){
        std::cout << "Exception Occured: " << ex.what() << std::endl;
        return 1;
    }

    gli::quit();

    return 0;
}