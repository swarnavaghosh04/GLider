#define HGL_DEBUG

#include "HermyGL/HermyGL.hpp"
#include "HermyGL/VertexArray.hpp"
#include "HermyGL/VertexBuffer.hpp"

inline void printError(const char* message, const hgl::error& e){
    SDL_Log("%s: [%d] %s (%d)\n", message, e.code, e.message, (int)(e.message != hgl::noError));
}

int main(int argc, const char* argv[]){

    hgl::error err;

    err = hgl::initialize();
    printError("Initialization", err);

    {
        SDL_Log(
            "Dimension:     %u\n"
            "LayoutElement: %u\n",
            sizeof(hgl::LayoutElement::Dimension),
            sizeof(hgl::LayoutElement)
        );

        hgl::Window window = {err, "Test Window", 500, 400, 0, 0};
        printError("Window Creation", err);

        unsigned int storage[2];

        const float data[4*4] = {
            2,3,4,5,
            3,2,1,4,
            3,2,3,4,
            2,3,4,1
        };

        hgl::VertexArray<hgl::stack> va(1, storage);
        hgl::VertexBuffer<hgl::stack> vb(1);

        vb.feedData<float>(data, 4*4, GL_STATIC_DRAW, 0);
        
        hgl::LayoutElement lay[2] = {{hgl::LayoutElement::TWO, false}, {hgl::LayoutElement::TWO, false}};
        hgl::Layout layout = {lay, 2};

        va.readBufferData<float>(vb, 0, layout, 0, 0);

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