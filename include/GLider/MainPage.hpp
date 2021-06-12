/**
 * @mainpage GLider - OpenGL C++ Class Abstraction
 * 
 * @section intro_sec Introduction
 * 
 * As from the title, it is clear that this is an OpenGL class abstraction library. It uses
 * <a href="https://www.libsdl.org/index.php">SDL2</a> for window management, 
 * <a href="https://github.com/g-truc/glm">GLM</a> for the required mathematics, and
 * <a href="https://glad.dav1d.de/">GLAD</a> for loading the OpenGL function
 * pointers. It is highly recommended to use a
 * <a href="https://cmake.org/cmake/help/v3.20/">CMake</a> based project 
 * since it manages all dependencies without a hassle. Support for Android and
 * eventually IOS will also be avaliable.
 * 
 * @section usage_sec Usage
 * 
 * To get the best idea on how to use this library, look at the
 * code for rendering a triangle:
 * 
 * @include test/triangle.cpp
 * 
 * @subsection sec_by_sec_desc Section by Section Description
 * 
 * @subsubsection shader_sources Shader Sources
 * @snippet test/triangle.cpp Shader Sources
 * 
 * This is the OpenGL shader source code. You can define a string, or you can
 * write it in a seperate file.
 * 
 * @subsubsection handle_cmd_args Handle Commandline Arguments
 * @snippet test/triangle.cpp Handle Cmd Args
 * 
 * This is not part of the GLider, but it helps for testing purposes. The code
 * is intended to see whether a valid float was passed in as the second command
 * line argument which will be used as the time (in milliseconds) for this
 * program to run and display the triangle.
 * 
 * @subsubsection init GLider Initialization
 * @snippet test/triangle.cpp GLider Init
 * 
 * This section initalizes all the component of GLider. It should always be
 * called before utilizing any GLider or SDL2 functions. At the end, GLider
 * should be closed as well.
 * 
 * @subsubsection vertices Vertex Data
 * @snippet test/triangle.cpp Vertices
 * 
 * Vertex data can be specified using any C++ standard container, as long as the
 * containers have `data()` and `size()` member functions.
 * 
 * @subsubsection window_creation Window Creation
 * @snippet test/triangle.cpp Window Creation
 * 
 * The first 3 lines deal with finding the correct dimension for the window.
 * A window can be created using the gli::OpenGLWindow class. The constuctor
 * used for this example accepts the window title, followed by the width and
 * height of the window. In this case, we are creating a window with 3/4 the
 * dimensions of the screen.
 * 
 * @subsubsection printing_info Printing Info
 * @snippet test/triangle.cpp Print OpenGL Info
 * 
 * This is just for information printing, but it also demonstrates that the user
 * is free to call OpenGL functions directly.
 * 
 * @subsubsection var_decl Glider Variable Declarations
 * @snippet test/triangle.cpp GLider Variable Declarations
 * 
 * Declares variables using GLider classes
 * 
 * @subsubsection store_to_vram Storing Vertex Data in VRAM
 * @snippet test/triangle.cpp Store Data in VRAM
 * 
 * These lines are responsible for feeding the vertex data to OpenGL and telling
 * it how to interpret the data. The first thing that needs to be done is to
 * feed the data into a vertex buffer (through a gli::Buffer<gli::VertexBuffer>
 * object). Once that is done, a vertex array is supposed to read and make sense
 * of the data. For this, we need to specify the structure of the data using an
 * array (or vector) of gli::LayoutElement objects.
 * 
 * @subsubsection ver_attrib_loc Vertex Attribute Locations
 * @snippet test/triangle.cpp Vertex Attribute Locations
 * 
 * We need to specify the appropriate vertex attribute locations so that the
 * shader can find those attributes. This step is not necessary if you decide to
 * use the `layout` qualifier within your shader source code.
 * 
 * @subsubsection shader_comp Shader Compilation
 * @snippet test/triangle.cpp Shader Compilation
 * 
 * A lot of the OpenGL shader compilation procedures are automated through
 * GLider. If you wrote your source code in a seperate file, you can use
 * `compileFile()` instead of `compileString()`.
 * 
 * @subsubsection ensure_bind Binding
 * @snippet test/triangle.cpp Ensure Bind
 * 
 * These lines just ensure that the correct objects are bound for OpenGl to read
 * from.
 * 
 * @subsubsection draw Rendering The Triangle
 * @snippet test/triangle.cpp Draw
 * 
 * Finally, we are ready to loop through, clear the color and depth buffers, and
 * draw the shape described by the data we spent so long organizing for OpenGL.
 * One thing to note is that we have the swap the buffers for any changes to
 * show up on the screen. 
 * 
 * @subsubsection event_handling Event Handling
 * @snippet test/triangle.cpp Event Handler
 * 
 * This section is better understood through SDL's documentation, but it is
 * clear what the intention is.
 * 
 * @subsubsection cloer Program Closer
 * @snippet test/triangle.cpp Program Close Handler
 * 
 * This section just determines whether the program should remain open or closed
 * after a certain time has passed
 * 
 * @subsubsection exit GLider Exit
 * @snippet test/triangle.cpp GLider Exit
 * 
 * As mentioned at the very start, the GLider program must be closed after it
 * has been initialized. This is done through a simple call to gli::quit().
 * 
*/