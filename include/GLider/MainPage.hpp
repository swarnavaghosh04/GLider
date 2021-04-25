#if 0
/**
 * @mainpage GLider - OpenGL C++ Class Abstraction
 * 
 * @section intro_sec Introduction
 * 
 * As from the title, it is clear that this is an OpenGL
 * class abstraction library. It uses
 * <a href="https://www.libsdl.org/index.php">SDL2</a> for
 * window management, 
 * <a href="https://github.com/g-truc/glm">GLM</a> for
 * the required mathematics, and
 * <a href="https://glad.dav1d.de/">GLAD</a> for loading
 * the OpenGL function pointers.
 * 
 * @section usage_sec Usage
 * 
 * To get the best idea on how to use this library, look at the
 * code for rendering a triangle:
 * <a href="https://github.com/swarnavaghosh04/GLider/blob/main/test/triangle.cpp">
 * triangle.cpp
 * </a>
 * 
 * Here is a step by step guide as to what that program does:
 * 
 * 1. gli::initialize() with OpenGL 3.0
 * 2. Creates an array of vertices
 * 3. Creates a window that has 3/4 dimensions of the
 *    screen
 * 4. Declared @ref VertexArray, @ref VertexBuffer, and @ref Shaders objects
 * 5. feeds the data of the vertices to the GPU through VertexBuffer
 * 6. VertexArray makes sense of the VertexBuffer data by reading it in a specific 
 *    structure defined by an array of @ref LayoutElement
 * 7. Compiles, links and validates shaders
 * 8. Bind necessary objects
 * 9. Draw loop where the buffer is being cleared, new triangle is being drawn, and
 *    the buffer is being swapped. Then the SDL2 events are handled. Consult
 *    <a href="https://www.libsdl.org/index.php"> SDL2</a> documentation for more
 *    details
 * 10. gli::quit() at the end 
*/
#endif