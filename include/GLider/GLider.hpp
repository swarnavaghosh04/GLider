/*
MIT License

Copyright (c) 2021 Swarnava Ghosh

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice (including the
next paragraph) shall be included in all copies or substantial portions
of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @mainpage GLider - OpenGL C++ Class Abstraction
 * 
 * @section intro_sec Introduction
 * 
 * As from the title, it is clear that this is an OpenGL
 * class abstraction library. It uses
 * <a href="https://www.libsdl.org/index.php">SDL2</a> for
 * window management, and
 * <a href="https://github.com/g-truc/glm">GLM</a> for
 * the required mathematics.
*/

/**
 * @file GLider.hpp
 * @brief Main header file for GLider which includes all other header files
*/

#ifndef GLIDER__H_
#define GLIDER__H_

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include "GLider/GLider_core.hpp"
#include "GLider/Window.hpp"
#include "GLider/VertexArray.hpp"
#include "GLider/Buffer.hpp"
#include "GLider/Shaders.hpp"
#include "GLider/FrameRate.hpp"

namespace gli{

    typedef gladGLversionStruct OpenGLVersion;

    /**
     * @brief Initializes all subsystems for SDL2
     * 
     * This should be called before using any funtions from
     * GLider. It initlializes all the subsystems for SDL2
     * and sets important attributes.
     * 
     * @note When `HGL_DEBUG` is defined, this function
     * will set the priority of `SDL_LOG_CATEGORY_APPLICATION`
     * to `SDL_LOG_PRIORITY_DEBUG`.
     * 
     * @param major is the major version for OpenGL to be initialized. should be greater than 3.
     * @param minor is the minor version for OpenGL to be initialized. defaults to 0.
     * 
     * @throws std::invalid_argument invalid OpenGL version.
     * @throws std::runtime_error SDL2 could not be initialized or GL attributes could not be set.
    */
    void initialize(int major=3, int minor=0);

    /**
     * @brief Quits SDL2
     * 
     * Should be called after @ref initialize has been called.
    */
    void quit() noexcept;

}

#endif
