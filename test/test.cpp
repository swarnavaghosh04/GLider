#include "HermyGL/HermyGL.hpp"
#include "HermyGL/VertexArray.hpp"
#include "HermyGL/VertexBuffer.hpp"

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

        const float data[4*4] = {
            2,3,4,5,
            3,2,1,4,
            3,2,3,4,
            2,3,4,1
        };
        const hgl::LayoutElement dataLayout[2] = {
            {hgl::Dim_THREE, hgl::Norm_FALSE},
            {hgl::Dim_ONE, hgl::Norm_FALSE}
        };

        hgl::VertexArray va;
        hgl::VertexBuffer vb;

        vb.feedData<float>(data, 4*4, dataLayout, 2, GL_STATIC_DRAW);
        va.readBufferData<float>(vb, 0);

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