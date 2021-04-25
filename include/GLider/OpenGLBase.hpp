#ifndef GLI_OPENGL_BASE__H_
#define GLI_OPENGL_BASE__H_

#include <glm/glm.hpp>
#include "GLider/GLider_core.hpp"
#include "GLider/GLErrorHandling.hpp"

// #if GL_VERSION_4_0
//     #define INCORPORATE_DOUBLE
// #endif

namespace gli{

    /**
     * @brief Converts primitive datatypes to OpenGL definitions
     * 
     * @tparam T is the specified primitive type. can only be `char`, `short` or `int` along with their unsigned variants, or `float` or `double`
     * @return OpenGL definition like GL_FLOAT, GL_UNSIGNED_INT, etc. If the input is not valid, a value of 0 is returned
    */
    template<typename T>
    constexpr unsigned int getOpenGLTypeEnum() noexcept{

        constexpr int returnValue = 
            std::is_same<T, char>()             ? GL_BYTE :
            std::is_same<T, unsigned char>()    ? GL_UNSIGNED_BYTE :
            std::is_same<T, short>()            ? GL_SHORT :
            std::is_same<T, unsigned short>()   ? GL_UNSIGNED_SHORT:
            std::is_same<T, int>()              ? GL_INT :
            std::is_same<T, unsigned int>()     ? GL_UNSIGNED_INT :
            std::is_same<T, float>()            ? GL_FLOAT :
            // #ifdef INCORPORATE_DOUBLE
            std::is_same<T, double>()           ? GL_DOUBLE :
            // #endif
            0;
        static_assert(returnValue, "Invalid data type");
        return returnValue;
    }

    enum Dimension : unsigned char{
        D1 = 1, D2 = 2, D3 = 3, D4 = 4
    };

    enum DrawType : unsigned int{
        // #if GL_VERSION_2_0
        DrawPoints          = GL_POINTS,
        DrawLineStrip       = GL_LINE_STRIP,
        DrawLineLoop        = GL_LINE_LOOP,
        DrawLines           = GL_LINES,
        DrawTriangleStrip   = GL_TRIANGLE_STRIP,
        DrawTriangleFan     = GL_TRIANGLE_FAN,
        DrawTriangles       = GL_TRIANGLES,
        // #if !GL_VERSION_3_0
        DrawQuadStrip       = GL_QUAD_STRIP,
        DrawQuads           = GL_QUADS,
        DrawPolygon         = GL_POLYGON,
        // #endif
        // #endif
        // #if GL_VERSION_3_2
        DrawLineStripAdjacency      = GL_LINE_STRIP_ADJACENCY,
        DrawLinesAdjacency          = GL_LINES_ADJACENCY,
        DrawTriangleStripAdjacency  = GL_TRIANGLE_STRIP_ADJACENCY,
        DrawTrianglesAdjacency      = GL_TRIANGLES_ADJACENCY,
        // #endif
        // #if GL_VERSION_4_0
        DrawPatches                 = GL_PATCHES,
        // #endif
    };

    enum BufferBit : unsigned int{
        ColorBufferBit      = GL_COLOR_BUFFER_BIT,
        DepthBufferBit      = GL_DEPTH_BUFFER_BIT,
        StencilBufferBit    = GL_STENCIL_BUFFER_BIT,
    };

    enum Capability_NI : unsigned int{
        ClipDistance = GL_CLIP_DISTANCE0,
        ColorLogicOp = GL_COLOR_LOGIC_OP,
        CullFace = GL_CULL_FACE,
        DepthClamp = GL_DEPTH_CLAMP,
        DepthTest = GL_DEPTH_TEST,
        Dither = GL_DITHER,
        FramebufferSRGB = GL_FRAMEBUFFER_SRGB,
        LineSmooth = GL_LINE_SMOOTH,
        Multisample = GL_MULTISAMPLE,
        PolygonOffsetFill = GL_POLYGON_OFFSET_FILL,
        PolygonOffsetLine = GL_POLYGON_OFFSET_LINE,
        PolygonOffsetPoint = GL_POLYGON_OFFSET_POINT,
        PolygonSmooth = GL_POLYGON_SMOOTH,
        SampleAlphaToCoverage = GL_SAMPLE_ALPHA_TO_COVERAGE,
        SampleAlpheToOne = GL_SAMPLE_ALPHA_TO_ONE,
        SampleCoverage = GL_SAMPLE_COVERAGE,
        StencilTest = GL_STENCIL_TEST,
        ProgramPointSize = GL_PROGRAM_POINT_SIZE,
        // #if GL_VERSION_3_1
        PrimitiveRestart = GL_PRIMITIVE_RESTART,
        // #endif
        // #if GL_VERSION_3_2
        TextureCubeMapSeamless = GL_TEXTURE_CUBE_MAP_SEAMLESS,
        // #endif
        // #if GL_VERSION_4_3
        PrimitiveRestartFixedIndex = GL_PRIMITIVE_RESTART_FIXED_INDEX,
        DebugOutput = GL_DEBUG_OUTPUT,
        DebugOutputSynchronous = GL_DEBUG_OUTPUT_SYNCHRONOUS,
        // #endif
    };

    enum Capability_I : unsigned int{
        Blend = GL_BLEND,
        ScissorTest = GL_SCISSOR_TEST,
    };

    template<class Derived>
    class OpenGLBase{
        template<class Derived2>
        friend class Binder;
    protected:
        unsigned int id;
        OpenGLBase(unsigned int id) noexcept;         // Create Constructor from unsigned int in Derived class under private scope
        static void bindID(unsigned int id) noexcept; // Define in Derived class under private scope
        static unsigned int getBoundID() noexcept;    // Define in Derived class under private scope
    public:
        OpenGLBase() noexcept = default;
        OpenGLBase(const OpenGLBase<Derived>&) = delete;
        OpenGLBase(OpenGLBase<Derived>&& other) noexcept;
        OpenGLBase<Derived>& operator= (const OpenGLBase<Derived>&) = delete;
        OpenGLBase<Derived>& operator= (OpenGLBase<Derived>&& other) noexcept;
        void bind() const noexcept;
        static void bind(const OpenGLBase<Derived>& toBeBound) noexcept;
        static void unbind() noexcept;
        static OpenGLBase<Derived> getBound() noexcept;
        bool isBound() const noexcept;
        const unsigned int& getID() const noexcept {return id;}
        unsigned int& getID() noexcept {return id;}
    };

    template<class Derived>
    class Binder{
    private:
        const OpenGLBase<Derived>& prev;
    public:
        Binder(const OpenGLBase<Derived>& base) noexcept;
        ~Binder() noexcept;
    };

    void clear(BufferBit mask) noexcept;
    void enable(Capability_NI cap) noexcept;
    void enable(Capability_I cap) noexcept;
    void enable(Capability_I cap, unsigned int index) noexcept;
    void disable(Capability_NI cap) noexcept;
    void disable(Capability_I cap) noexcept;
    void disable(Capability_I cap, unsigned int index) noexcept;
    template<typename FLOAT_OR_DOUBLE>
    void depthRange(FLOAT_OR_DOUBLE near, FLOAT_OR_DOUBLE far) noexcept;
}

#include "GLider/impl/OpenGLBase.inl"

#endif