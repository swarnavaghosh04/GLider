/*
MIT License

Copyright (c) 2021 Swarnava Ghosh

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice (including the next paragraph) shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file HermyGL.hpp
 * @brief Main include file for HermyGL
*/

#ifndef HERMYGL__H_
#define HERMYGL__H_

#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include "HermyGL/HermyGL_core.hpp"
#include "HermyGL/Window.hpp"
#include "HermyGL/VertexArray.hpp"
#include "HermyGL/Buffer.hpp"
#include "HermyGL/Shaders.hpp"
#include "HermyGL/FrameRate.hpp"

namespace hgl{

    typedef gladGLversionStruct OpenGLVersion;

    /**
     * @brief Initializes all subsystems for SDL2
     * 
     * This should be called before using any funtions from
     * HermyGL. It initlializes all the subsystems for SDL2
     * and sets important attributes
    */
    HERMYGL_EXPORT void initialize(int major=3, int minor=0);
    HERMYGL_EXPORT void quit() noexcept;

}

#endif