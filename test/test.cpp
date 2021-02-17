#include "HermyGL/HermyGL.hpp"
#include "HermyGL/VertexArray.hpp"
#include "HermyGL/OpenGLBuffer.hpp"

inline void printError(const char* message, const hgl::error& e){
    SDL_Log("%s: [%d] %s\n", message, e.code, e.message);
}

int main(int argc, const char* argv[]){

    hgl::error err;

    err = hgl::initialize();
    printError("Initialization", err);

    {

        hgl::Window window = {err, "Test Window", 1000, 800, 0, 0};
        printError("Window Creation", err);

        const float vertexBufData[8*3] = {
             .5f,  .5f,  .5f,   // 0
            -.5f,  .5f,  .5f,   // 1
            -.5f, -.5f,  .5f,   // 2
             .5f, -.5f,  .5f,   // 3
             .5f,  .5f, -.5f,   // 4
            -.5f,  .5f, -.5f,   // 5
            -.5f, -.5f, -.5f,   // 6
             .5f, -.5f, -.5f    // 7
        };
        const hgl::LayoutElement dataLayout[1] = {
            {hgl::Dim_THREE, hgl::Norm_FALSE}
        };

        const unsigned char indexBufData[6*6] = {
            0, 1, 3, 1, 3, 2,
            1, 0, 5, 0, 5, 4,
            6, 5, 7, 5, 7, 4,
            2, 3, 6, 3, 6, 7,
            0, 3, 4, 3, 4, 7,
            2, 1, 6, 1, 6, 5
        };

        hgl::VertexArray va;
        hgl::OpenGLBuffer<hgl::VertexBuffer> vb;
        hgl::OpenGLBuffer<hgl::IndexBuffer> ib;
        va.bind();
        vb.bind();
        ib.bind();

        vb.feedData<float>(vertexBufData, 4*4, GL_STATIC_DRAW);
        ib.feedData<unsigned char>(indexBufData, 6*6, GL_STATIC_DRAW);

        va.readBufferData<float>(vb, dataLayout, 1, 0);

        bool keepRunning = true;
        SDL_Event e;

        while(keepRunning){

            while(SDL_PollEvent(&e)){
                if(e.type == SDL_QUIT){
                    keepRunning = false;
                    break;
                }
            }
        
        }

    }

    hgl::quit();

    return 0;

}