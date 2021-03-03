#include "HermyGL/HermyGL.hpp"

int main(int argc, const char** argv){

    try{

        hgl::initialize();

        std::array<float, 2*3> vertecies = {
            -.5, -.5,
            0,  .5,
            .5, -.5
        };

        hgl::Window win{"Triangle", 800, 800};

        hgl::VertexArray va;
        hgl::Buffer<hgl::VertexBuffer> vb;

        vb.feedData(vertecies, hgl::UseStaticDraw);

        va.bind();
        vb.bind();

        


        hgl::quit();

    }catch(std::exception& e){
        SDL_Log("Error Occured: %s\n", typeid(e).name());
        SDL_Log(e.what());
    }

}