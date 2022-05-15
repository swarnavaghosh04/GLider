#include "GLider/GLider.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

namespace gli{

    #if GLI_DEBUG

    std::stringstream initErrorMessage(const char* funcName, unsigned int firstErrCode){
        std::stringstream output(std::ios_base::out);
        output
            << "[OpenGL Error] "
            << funcName << " : "
            << std::setfill('0')
            << std::setw(6)
            << std::internal
            << std::hex
            << std::showbase
            << firstErrCode;
        return output;
    }

    void output_remaining_errors_into(std::ostream& out){

        auto errCode = glad_glGetError();

        while(errCode != GL_NO_ERROR){
            out << ", "
                << std::setfill('0')
                << std::setw(6)
                << std::internal
                << std::hex
                << std::showbase
                << errCode;
            errCode = glad_glGetError();
        }

    }

    void debug_callback(const char *funcName, void *funcptr, int len_args, ...){

        (void)funcptr;
        (void)len_args;

        const unsigned int firstErrCode = glad_glGetError();
        const bool errorOccured = firstErrCode != GL_NO_ERROR;

        if(errorOccured){
            std::stringstream message = initErrorMessage(funcName, firstErrCode);
            output_remaining_errors_into(message);
            throw std::runtime_error(message.str());
        }

    }

    #endif
    
    void initialize(){

        if(!gladLoadGL())
            throw std::runtime_error("GLAD Unable to load OpenGL");
        
        #ifdef GLAD_DEBUG
        glad_set_post_callback(debug_callback);
        #endif
    }

    
    void initialize(GLADloadproc loader){

        if(!gladLoadGLLoader(loader))
            throw std::runtime_error("GLAD Unable to load OpenGL");
        
        #ifdef GLAD_DEBUG
        glad_set_post_callback(debug_callback);
        #endif
    }

}




