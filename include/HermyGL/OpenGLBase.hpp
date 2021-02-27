#ifndef HGL_OPENGL_BASE__H_
#define HGL_OPENGL_BASE__H_

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "HermyGL/HermyGL_core.hpp"
#include "HermyGL/GLErrorHandling.hpp"

#define HGL_DATA_ALLOC_STACK 0
#define HGL_DATA_ALLOC_HEAP 1

#if GL_VERSION_4_0
    #define INCORPORATE_DOUBLE
#endif

namespace hgl{

    /**
     * @brief Converts privitive datatypes to OpenGL definitions
     * 
     * 
     * @tparam T is the specified primitive type. can only be `char`, `short` or `int` along with their unsigned variants, or `float` or `double`
     * @return OpenGL definition like GL_FLOAT, GL_UNSIGNED_INT, etc. If the input is not valid, a value of 0 is returned
    */
    template<typename T>
    constexpr unsigned int primitiveTypeToGLType(){
        return (
            std::is_same<T, char>()             ? GL_BYTE :
            std::is_same<T, unsigned char>()    ? GL_UNSIGNED_BYTE :
            std::is_same<T, short>()            ? GL_SHORT :
            std::is_same<T, unsigned short>()   ? GL_UNSIGNED_SHORT:
            std::is_same<T, int>()              ? GL_INT :
            std::is_same<T, unsigned int>()     ? GL_UNSIGNED_INT :
            std::is_same<T, float>()            ? GL_FLOAT :
            #ifdef INCORPORATE_DOUBLE
            std::is_same<T, double>()           ? GL_DOUBLE :
            #endif
            0
        );
    }

    
    enum Dimension : unsigned char{
        D1 = 1, D2 = 2, D3 = 3, D4 = 4
    };

    enum DrawType : unsigned int{
        #if GL_VERSION_2_0
        DrawPoints          = GL_POINTS,
        DrawLineStrip       = GL_LINE_STRIP,
        DrawLineLoop        = GL_LINE_LOOP,
        DrawLines           = GL_LINES,
        DrawTriangleStrip   = GL_TRIANGLE_STRIP,
        DrawTriangleFan     = GL_TRIANGLE_FAN,
        DrawTriangles       = GL_TRIANGLES,
        #if !GL_VERSION_3_0
        DrawQuadStrip       = GL_QUAD_STRIP,
        DrawQuads           = GL_QUADS,
        DrawPolygon         = GL_POLYGON,
        #endif
        #endif
        #if GL_VERSION_3_2
        DrawLineStripAdjacency      = GL_LINE_STRIP_ADJACENCY,
        DrawLinesAdjacency          = GL_LINES_ADJACENCY,
        DrawTriangleStripAdjacency  = GL_TRIANGLE_STRIP_ADJACENCY,
        DrawTrianglesAdjacency      = GL_TRIANGLES_ADJACENCY,
        #endif
        #if GL_VERSION_4_0
        DrawPatches                 = GL_PATCHES,
        #endif

    };

    enum BufferBit : unsigned int{
        ColorBufferBit      = GL_COLOR_BUFFER_BIT,
        DepthBufferBit      = GL_DEPTH_BUFFER_BIT,
        StencilBufferBit    = GL_STENCIL_BUFFER_BIT,
        #if GL_VERSION_2_1 && !GL_VERSION_3_0
        AccumBufferBit      = GL_ACCUM_BUFFER_BIT,
        #endif
    };

    enum Capability : unsigned int{
        Blend = GL_BLEND,
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
        ScissorTest = GL_SCISSOR_TEST,
        StencilTest = GL_STENCIL_TEST,
        ProgramPointSize = GL_PROGRAM_POINT_SIZE,
        #if GL_VERSION_3_1
        PrimitiveRestart = GL_PRIMITIVE_RESTART,
        #endif
        #if GL_VERSION_3_2
        TextureCubeMapSeamless = GL_TEXTURE_CUBE_MAP_SEAMLESS,
        #endif
    };


    // enum Capability : unsigned int{
    //     #if GL_VERSION_1_1
    //     PolygonOffsetFill = GL_POLYGON_OFFSET_FILL,
    //     PolygonOffsetLine = GL_POLYGON_OFFSET_LINE,
    //     PolygonOffsetPoint = GL_POLYGON_OFFSET_POINT,
    //     ColorLogicOp = GL_COLOR_LOGIC_OP,
    //     IndexLogicOp = GL_INDEX_LOGIC_OP,
    //     #endif
    //     #if GL_VERSION_1_2
    //     RescaleNormal = GL_RESCALE_NORMAL,
    //     Texture3D = GL_TEXTURE_3D,
    //     #endif
    //     #if GL_VERSION_1_3
    //     MultiSample = GL_MULTISAMPLE,
    //     SampleAlphaToCoverage = GL_SAMPLE_ALPHA_TO_COVERAGE,
    //     SampleAlphToOne = GL_SAMPLE_ALPHA_TO_ONE,
    //     SampleCoverage = GL_SAMPLE_COVERAGE,
    //     TextureCubeMap = GL_TEXTURE_CUBE_MAP,
    //     #endif
    //     #if GL_VERSION_1_3 | GL_ARB_multitexture
    //     Texture1D = GL_TEXTURE_1D,
    //     Texture2D = GL_TEXTURE_2D,
    //     TextureGenS = GL_TEXTURE_GEN_S,
    //     TextureGenT = GL_TEXTURE_GEN_T,
    //     TextureGenR = GL_TEXTURE_GEN_R,
    //     TextureGenQ = GL_TEXTURE_GEN_Q,
    //     #endif
    //     #if GL_VERSION_2_0
    //     PointSprite = GL_POINT_SPRITE,
    //     VertexProgramPointSize = GL_VERTEX_PROGRAM_POINT_SIZE,
    //     VertexProgramTwoSided = GL_VERTEX_PROGRAM_TWO_SIDE,
    //     #endif
    //     #if GL_ARB_imaging
    //     ColorTable = GL_COLOR_TABLE,
    //     Convolution1D = GL_CONVOLUTION_1D,
    //     Convolution2D = GL_CONVOLUTION_2D,
    //     Histogram = GL_HISTOGRAM,
    //     MinMax = GL_MINMAX,
    //     PostColorMatrixColorTable = GL_POST_COLOR_MATRIX_COLOR_TABLE,
    //     PostConvolutionColorTable = GL_POST_CONVOLUTION_COLOR_TABLE,
    //     Separable2D = GL_SEPARABLE_2D,
    //     #endif
    //     #if GL_VERSION_2_1
    //     AlphaTest = GL_ALPHA_TEST,
    //     AutoNormal = GL_AUTO_NORMAL,
    //     Blend = GL_BLEND,
    //     ClipPlane0 = GL_CLIP_PLANE0,
    //     ColorMaterial = GL_COLOR_MATERIAL,
    //     ColorSum = GL_COLOR_SUM,
    //     CullFase = GL_CULL_FACE,
    //     DepthTest = GL_DEPTH_TEST,
    //     Dither = GL_DITHER,
    //     Fog = GL_FOG,
    //     Light0 = GL_LIGHT0,
    //     Lighting = GL_LIGHTING,
    //     LineSmooth = GL_LINE_SMOOTH,
    //     LineStipple = GL_LINE_STIPPLE,
    //     Map1Color4 = GL_MAP1_COLOR_4,
    //     Map1Index = GL_MAP1_INDEX,
    //     Map1Normal = GL_MAP1_NORMAL,
    //     Map1TextureCoord1 = GL_MAP1_TEXTURE_COORD_1,
    //     Map1TextureCoord2 = GL_MAP1_TEXTURE_COORD_2,
    //     Map1TextureCoord3 = GL_MAP1_TEXTURE_COORD_3,
    //     Map1TextureCoord4 = GL_MAP1_TEXTURE_COORD_4,
    //     Map1Vertex3 = GL_MAP1_VERTEX_3,
    //     Map1Vertex4 = GL_MAP1_VERTEX_4,
    //     Map2Color4 = GL_MAP2_COLOR_4,
    //     Map2Index = GL_MAP2_INDEX,
    //     Map2Normal = GL_MAP2_NORMAL,
    //     Map2TextureCoord1 = GL_MAP2_TEXTURE_COORD_1,
    //     Map2TextureCoord2 = GL_MAP2_TEXTURE_COORD_2,
    //     Map2TextureCoord3 = GL_MAP2_TEXTURE_COORD_3,
    //     Map2TextureCoord4 = GL_MAP2_TEXTURE_COORD_4,
    //     Map2Vertex3 = GL_MAP2_VERTEX_3,
    //     Map2Vertex4 = GL_MAP2_VERTEX_4,
    //     Normalize = GL_NORMALIZE,
    //     PointSmooth = GL_POINT_SMOOTH,
    //     PolygonSmooth = GL_POLYGON_SMOOTH,
    //     PolygonStipple = GL_POLYGON_STIPPLE,
    //     ScissorTest = GL_SCISSOR_TEST,
    //     StencilTest = GL_STENCIL_TEST,
    //     #endif

    // };

    // #ifdef INCORPORATE_DOUBLE
    //     #define __HGL_InstantiateTemplateDouble(declarationMacro, ...)\
    //         declarationMacro(double, ## __VA_ARGS__);
    // #else
    //     #define __HGL_InstantiateTemplateDouble(declarationMacro, ...)
    // #endif

    // #define __HGL_InstantiateTemplateTypes(declarationMacro, ...)\
    //     declarationMacro(char              ,## __VA_ARGS__);\
    //     declarationMacro(unsigned char     ,## __VA_ARGS__);\
    //     declarationMacro(short             ,## __VA_ARGS__);\
    //     declarationMacro(unsigned short    ,## __VA_ARGS__);\
    //     declarationMacro(int               ,## __VA_ARGS__);\
    //     declarationMacro(unsigned int      ,## __VA_ARGS__);\
    //     declarationMacro(float             ,## __VA_ARGS__);\
    //     __HGL_InstantiateTemplateDouble(declarationMacro, ##__VA_ARGS__)
        
    class HERMYGL_EXPORT OpenGLBase{
    protected:
        unsigned int id;
    public:
        OpenGLBase() = default;
        virtual ~OpenGLBase();
        OpenGLBase(const OpenGLBase&) = delete;
        OpenGLBase(OpenGLBase&& other) noexcept(true);
        OpenGLBase& operator= (const OpenGLBase&) = delete;
        OpenGLBase& operator= (OpenGLBase&& other) noexcept(true);
        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        const unsigned int getId() const;
    };

    void clear(hgl::BufferBit mask);
    void enable(hgl::Capability cap);
    void disable(hgl::Capability cap);

}

#include "HermyGL/OpenGLBase.inl"

#endif