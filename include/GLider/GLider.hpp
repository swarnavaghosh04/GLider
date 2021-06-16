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
 * @file GLider.hpp
 * @brief Main header file for GLider which includes all other header files
*/

#ifndef GLIDER__H_
#define GLIDER__H_

#include "GLider/GLider_core.hpp"
#include "GLider/Window.hpp"
#include "GLider/VertexArray.hpp"
#include "GLider/Buffer.hpp"
#include "GLider/ShaderProgram.hpp"
#include "GLider/FrameRate.hpp"

#include <array>
#include <vector>
#include <list>
#include <functional>

/**
 * GLider namespace
 */
namespace gli{

    //! @private
    void checkVersion(int major, int minor);

    /**
     * @{
     * @name initializers
     * @anchor initializers
     */

    template<std::size_t N>
    using SDLAttributeArray = std::array<std::pair<SDL_GLattr, int>, N>;
    using SDLAttributeList = std::list<std::pair<SDL_GLattr, int>>;
    using SDLAttributeVector = std::vector<std::pair<SDL_GLattr, int>>;

    //! @private
    void initialize_base(int major, int minor, const std::function<void(int&)>& attributeSetter);

    /**
     * @brief Initializes all subsystems for SDL2 with default SDL2 attributes
     * 
     * This, or any other overload of this function, should
     * be called before using any funtions from GLider.
     * It initlializes all the subsystems for SDL2
     * and sets important attributes.
     * 
     * @remark When `GLI_DEBUG` is defined, this function
     * will set the priority of `SDL_LOG_CATEGORY_APPLICATION`
     * to `SDL_LOG_PRIORITY_DEBUG`.
     * 
     * @remark This function will initate SDL2 with  the following
     * attributes:
     *  - `SDL_GL_CONTEXT_PROFILE_MASK = SDL_GL_CONTEXT_PROFILE_CORE`
     *  - `SDL_GL_CONTEXT_MAJOR_VERSION =` @p major
     *  - `SDL_GL_CONTEXT_MINOR_VERSION =` @p minor
     *  - `SDL_GL_DOUBLEBUFFER = 1`
     *  - `SDL_GL_DEPTH_SIZE = 32`
     *  - `SDL_GL_MULTISAMPLEBUFFERS = 1`
     *  - `SDL_GL_MULTISAMPLESAMPLES = 4`
     *  - `SDL_GL_ACCELERATED_VISUAL = 1`
     * 
     * @remark if you want to have different attributes, use one of the
     * overloads of this function.
     * 
     * @param[in] major the major version for OpenGL to be initialized. should be greater than 3.
     * @param[in] minor the minor version for OpenGL to be initialized. defaults to 0.
     * 
     * @throws std::invalid_argument invalid OpenGL version.
     * @throws std::runtime_error SDL2 could not be initialized or GL attributes could not be set.
     * 
     * @see
     *  - @ref gli::initialize(int, int, const gli::SDLAttributeArray<N>&)
     *  - @ref gli::initialize(int, int, const gli::SDLAttributeList&)
     *  - @ref gli::initialize(int, int, const gli::SDLAttributeVector&)
     */
    void initialize(int major=3, int minor=0);

    

    /**
     * @overload
     * @brief Initializes all subsystems for SDL2
     * 
     * This, or any other overload of this function, should
     * be called before using any funtions from GLider.
     * It initlializes all the subsystems for SDL2
     * and sets important attributes.
     * 
     * @remark When `GLI_DEBUG` is defined, this function
     * will set the priority of `SDL_LOG_CATEGORY_APPLICATION`
     * to `SDL_LOG_PRIORITY_DEBUG`.
     * 
     * @remark The following 3 attributes will always take up the 
     * following values after this function call regardless
     * of the value passed in through @p attributes:
     *  - `SDL_GL_CONTEXT_PROFILE_MASK = SDL_GL_CONTEXT_PROFILE_CORE`
     *  - `SDL_GL_CONTEXT_MAJOR_VERSION =` @p major
     *  - `SDL_GL_CONTEXT_MINOR_VERSION =` @p minor
     * 
     * @param[in] major the major version for OpenGL to be initialized. should be greater than 3.
     * @param[in] minor the minor version for OpenGL to be initialized. defaults to 0.
     * @param[in] attributes `std::array` of `std::pair<SDL_GLattr, int>` specifying user SDL attribute values.
     * @tparam N number of `std::pair` objects inside attributes.
     * 
     * @throws std::invalid_argument invalid OpenGL version.
     * @throws std::runtime_error SDL2 could not be initialized or GL attributes could not be set.
     * 
     * @see
     * @ref gli::SDLAttributeArray
     */
    template<std::size_t N>
    void initialize(int major, int minor, const SDLAttributeArray<N>& attributes);

    /// @private
    template<typename T>
    void initialize(int major, int minor, const T& attributes);

    /**
     * @overload
     * @brief Initializes all subsystems for SDL2
     * 
     * This, or any other overload of this function, should
     * be called before using any funtions from GLider.
     * It initlializes all the subsystems for SDL2
     * and sets important attributes.
     * 
     * @remark When `GLI_DEBUG` is defined, this function
     * will set the priority of `SDL_LOG_CATEGORY_APPLICATION`
     * to `SDL_LOG_PRIORITY_DEBUG`.
     * 
     * @remark The following 3 attributes will always take up the 
     * following values after this function call regardless
     * of the value passed in through @p attributes:
     *  - `SDL_GL_CONTEXT_PROFILE_MASK = SDL_GL_CONTEXT_PROFILE_CORE`
     *  - `SDL_GL_CONTEXT_MAJOR_VERSION =` @p major
     *  - `SDL_GL_CONTEXT_MINOR_VERSION =` @p minor
     * 
     * @param[in] major the major version for OpenGL to be initialized. should be greater than 3.
     * @param[in] minor the minor version for OpenGL to be initialized. defaults to 0.
     * @param[in] attributes `std::list` of `std::pair<SDL_GLattr, int>` specifying user SDL attribute values.
     * 
     * @throws std::invalid_argument invalid OpenGL version.
     * @throws std::runtime_error SDL2 could not be initialized or GL attributes could not be set.
     * 
     * @see
     * @ref gli::SDLAttributeList
     */
    extern template void initialize(int major, int minor, const SDLAttributeList& attributes);

    /**
     * @overload
     * @brief Initializes all subsystems for SDL2
     * 
     * This, or any other overload of this function, should
     * be called before using any funtions from GLider.
     * It initlializes all the subsystems for SDL2
     * and sets important attributes.
     * 
     * @remark When `GLI_DEBUG` is defined, this function
     * will set the priority of `SDL_LOG_CATEGORY_APPLICATION`
     * to `SDL_LOG_PRIORITY_DEBUG`.
     * 
     * @remark The following 3 attributes will always take up the 
     * following values after this function call regardless
     * of the value passed in through @p attributes:
     *  - `SDL_GL_CONTEXT_PROFILE_MASK = SDL_GL_CONTEXT_PROFILE_CORE`
     *  - `SDL_GL_CONTEXT_MAJOR_VERSION =` @p major
     *  - `SDL_GL_CONTEXT_MINOR_VERSION =` @p minor
     * 
     * @param[in] major the major version for OpenGL to be initialized. should be greater than 3.
     * @param[in] minor the minor version for OpenGL to be initialized. defaults to 0.
     * @param[in] attributes `std::vector` of `std::pair<SDL_GLattr, int>` specifying user SDL attribute values.
     * 
     * @throws std::invalid_argument invalid OpenGL version.
     * @throws std::runtime_error SDL2 could not be initialized or GL attributes could not be set.
     * 
     * @see
     * @ref gli::SDLAttributeVector
     */
    extern template void initialize(int major, int minor, const SDLAttributeVector& attributes);

    /// @}

    /**
     * @brief Quits SDL2
     * 
     * Should be called after at the very end of your program
     * (and after one of the @ref initializers have been called)
     */
    void quit() noexcept;

}

#include "GLider/impl/GLider.inl"

#endif
