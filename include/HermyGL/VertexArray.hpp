#ifndef HGL_VERTEXARRAY__H_
#define HGL_VERTEXARRAY__H_

#include "HermyGL/OpenGLBase.hpp"
#include "HermyGL/OpenGLBuffer.hpp"
//#include "HermyGL/VertexBuffer.hpp"

namespace hgl{

    enum Dimensions : unsigned char{
        Dim_ONE = 1, Dim_TWO = 2, Dim_THREE = 3, Dim_FOUR = 4
    };

    enum Normalized : bool{
        Norm_FALSE = false, Norm_TRUE = true
    };

    struct LayoutElement{
        Dimensions dimension;
        Normalized normalized;
    };

    enum DrawType : unsigned int{
        #if GL_VERSION_2_0
        DrawPoints          = GL_POINTS,
        DrawLineStrip       = GL_LINE_STRIP,
        DrawLineLoop        = GL_LINE_LOOP,
        DrawLines           = GL_LINES,
        DrawTriangleStrip   = GL_TRIANGLE_STRIP,
        DrawTriangleFan     = GL_TRIANGLE_FAN,
        DrawTriangles       = GL_TRIANGLES
        #if !GL_VERSION_3_0
        ,
        DrawQuadStrip       = GL_QUAD_STRIP,
        DrawQuads           = GL_QUADS,
        DrawPolygon         = GL_POLYGON
        #endif
        #endif
        #if GL_VERSION_3_2
        ,
        DrawLineStripAdjacency      = GL_LINE_STRIP_ADJACENCY,
        DrawLinesAdjacency          = GL_LINES_ADJACENCY,
        DrawTriangleStripAdjacency  = GL_TRIANGLE_STRIP_ADJACENCY,
        DrawTrianglesAdjacency      = GL_TRIANGLES_ADJACENCY
        #endif
        #if GL_VERSION_4_0
        ,
        DrawPatches                 = GL_PATCHES
        #endif

    };

    class HERMYGL_EXPORT VertexArray : public OpenGLBase{
    public:
        VertexArray();
        ~VertexArray();
        void bind() const;
        void unbind() const;
        template<typename T>
        void readBufferData(
            const OpenGLBuffer<VertexBuffer>&   vb,
            const LayoutElement*                layout,
            unsigned int                        layoutCount,
            unsigned int                        startingAttribIndex = 0
        );
        template<DrawType drawType>
        void draw();
    };

    #define TEMP_INST(T)\
        extern template void HERMYGL_EXPORT VertexArray::readBufferData<T>(\
            const OpenGLBuffer<VertexBuffer>&   vb,\
            const LayoutElement*                layout,\
            unsigned int                        layoutCount,\
            unsigned int                        startingAttribIndex = 0\
        )

    __HGL_InstantiateTemplateTypes(TEMP_INST);

    #undef TEMP_INST
    #define TEMP_INST(drawType)\
        extern template void HERMYGL_EXPORT VertexArray::draw<drawType>()

    #if GL_VERSION_2_0
    TEMP_INST(DrawPoints);
    TEMP_INST(DrawLineStrip);
    TEMP_INST(DrawLineLoop);
    TEMP_INST(DrawLines);
    TEMP_INST(DrawTriangleStrip);
    TEMP_INST(DrawTriangleFan);
    TEMP_INST(DrawTriangles);
    #if !GL_VERSION_3_0
    TEMP_INST(DrawQuadStrip);
    TEMP_INST(DrawQuads);
    TEMP_INST(DrawPolygon);
    #endif
    #endif
    #if GL_VERSION_3_2
    TEMP_INST(DrawLineStripAdjacency);
    TEMP_INST(DrawLinesAdjacency);
    TEMP_INST(DrawTriangleStripAdjacency);
    TEMP_INST(DrawTrianglesAdjacency);
    #endif
    #if GL_VERSION_4_0
    TEMP_INST(DrawPatches);
    #endif

    #undef TEMP_INST

}

#endif