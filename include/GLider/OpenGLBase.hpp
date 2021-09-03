#ifndef GLI_OPENGL_BASE__H_
#define GLI_OPENGL_BASE__H_

#include <glm/glm.hpp>
#include "GLider/GLider_core.hpp"
#include "GLider/GLErrorHandling.hpp"

#include <concepts>

#if GL_VERSION_4_0
    #define INCORPORATE_DOUBLE 1
#else
    #define INCORPORATE_DOUBLE 0
#endif

namespace gli{

    /** 
     * @private
     * credits: https://en.cppreference.com/w/cpp/concepts/same_as
    */
    template<typename T, typename ... U>
    concept IsAnyOf = (std::same_as<T, U> || ...);

    /**
     * Types that are acceptable to OpenGL.
    */
    template<typename T>
    concept OpenGLType = 
        (std::integral<T> && !IsAnyOf<T, long, unsigned long>) ||
        (std::floating_point<T>
        #if !INCORPORATE_DOUBLE
        && !std::same_as<T,double>
        #endif
        );

    enum OpenGLTypes : unsigned int{
        TypeByte = GL_BYTE,
        TypeUnsignedByte = GL_UNSIGNED_BYTE,
        TypeShort = GL_SHORT,
        TypeUnsignedShort = GL_UNSIGNED_SHORT,
        TypeInt = GL_INT,
        TypeUnsignedInt = GL_UNSIGNED_INT,
        TypeFixed = GL_FIXED,
        TypeHalfFloat = GL_HALF_FLOAT,
        TypeFloat = GL_FLOAT,
        #if INCORPORATE_DOUBLE
        TypeDouble = GL_DOUBLE,
        #endif
    };

    /**
     * @brief Converts primitive datatypes to OpenGL definitions
     * 
     * @tparam T is the specified primitive type. can only be `char`, `short` or `int` along with their unsigned variants, or `float` or `double`
     * @return OpenGL definition like GL_FLOAT, GL_UNSIGNED_INT, etc.
    */
    template<OpenGLType T>
    constexpr OpenGLTypes getOpenGLTypeEnum() noexcept{

        constexpr OpenGLTypes returnValue = 
            std::is_same<T, char>() ||
            std::is_same<T, signed char>()      ? TypeByte :
            std::is_same<T, unsigned char>()    ? TypeUnsignedByte :
            std::is_same<T, short>()            ? TypeShort :
            std::is_same<T, unsigned short>()   ? TypeUnsignedShort:
            std::is_same<T, int>()              ? TypeInt :
            std::is_same<T, unsigned int>()     ? TypeUnsignedInt :
            std::is_same<T, float>()            ? TypeFloat :
            #if INCORPORATE_DOUBLE
            std::is_same<T, double>()           ? TypeDouble :
            #endif
            static_cast<OpenGLTypes>(0);
        return returnValue;
    }

    constexpr std::size_t getSizeOfOpenGLType(unsigned int type){
        switch(type){
            case GL_BYTE:
            case GL_UNSIGNED_BYTE:
                return sizeof(char);
            case GL_SHORT:
            case GL_UNSIGNED_SHORT:
                return sizeof(short);
            case GL_INT:
            case GL_UNSIGNED_INT:
                return sizeof(int);
            case GL_FLOAT:
                return sizeof(float);
            case GL_DOUBLE:
                return sizeof(double);
        }
        return 0;
    }

    enum DrawType : unsigned int{
        DrawPoints          = GL_POINTS,
        DrawLineStrip       = GL_LINE_STRIP,
        DrawLineLoop        = GL_LINE_LOOP,
        DrawLines           = GL_LINES,
        DrawTriangleStrip   = GL_TRIANGLE_STRIP,
        DrawTriangleFan     = GL_TRIANGLE_FAN,
        DrawTriangles       = GL_TRIANGLES,
        #if GL_VERSION_3_2
        DrawLineStripAdjacency      = GL_LINE_STRIP_ADJACENCY,
        DrawLinesAdjacency          = GL_LINES_ADJACENCY,
        DrawTriangleStripAdjacency  = GL_TRIANGLE_STRIP_ADJACENCY,
        DrawTrianglesAdjacency      = GL_TRIANGLES_ADJACENCY,
        #if GL_VERSION_4_0
        DrawPatches                 = GL_PATCHES,
        #endif
        #endif
    };

    enum BufferBit : unsigned int{
        ColorBufferBit      = GL_COLOR_BUFFER_BIT,
        DepthBufferBit      = GL_DEPTH_BUFFER_BIT,
        StencilBufferBit    = GL_STENCIL_BUFFER_BIT,
    };

    enum Capability_NI : unsigned int{
        ClipDistance0 = GL_CLIP_DISTANCE0,
        ClipDistance1 = GL_CLIP_DISTANCE1,
        ClipDistance2 = GL_CLIP_DISTANCE2,
        ClipDistance3 = GL_CLIP_DISTANCE3,
        ClipDistance4 = GL_CLIP_DISTANCE4,
        ClipDistance5 = GL_CLIP_DISTANCE5,
        ClipDistance6 = GL_CLIP_DISTANCE6,
        ClipDistance7 = GL_CLIP_DISTANCE7,
        ColorLogicOp = GL_COLOR_LOGIC_OP,
        CullFace = GL_CULL_FACE,
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
        #if GL_VERSION_3_1
        PrimitiveRestart = GL_PRIMITIVE_RESTART,
        #if GL_VERSION_3_2
        DepthClamp = GL_DEPTH_CLAMP,
        ProgramPointSize = GL_PROGRAM_POINT_SIZE,
        TextureCubeMapSeamless = GL_TEXTURE_CUBE_MAP_SEAMLESS,
        #if GL_VERSION_4_3
        PrimitiveRestartFixedIndex = GL_PRIMITIVE_RESTART_FIXED_INDEX,
        DebugOutput = GL_DEBUG_OUTPUT,
        DebugOutputSynchronous = GL_DEBUG_OUTPUT_SYNCHRONOUS,
        #endif
        #endif
        #endif
    };

    enum Capability_I : unsigned int{
        Blend = GL_BLEND,
        ScissorTest = GL_SCISSOR_TEST,
    };

    //! @private
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
        unsigned int prevID;
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
    template<std::floating_point T>
    void depthRange(T near, T far) noexcept;

    //! @private
    template<template <typename, auto...> class T, typename U, auto... Args>
    concept StdContainer = requires(T<U, Args...> x){
        { x.size() } -> std::same_as<typename T<U, Args...>::size_type>;
        { x.data() } -> std::convertible_to<const void*>;
    };
}

#include "GLider/impl/OpenGLBase.inl"

#endif