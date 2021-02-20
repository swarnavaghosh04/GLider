#include "HermyGL/HermyGL.hpp"
#include "HermyGL/VertexArray.hpp"
#include "HermyGL/OpenGLBuffer.hpp"

const char* const vertexShader = R"CODE(
    #version 330 core
    layout(location=0) in vec2 position;
    void main(){
        gl_Position = vec4(position, 0.f, 1.f);
    }
)CODE";

const char* const fragmentShader = R"CODE(
    #version 330 core
    out vec4 FragColor;
    void main(){
        FragColor = vec4(0.3f, 0.3f, 0.6f, 1.f);
    }
)CODE";

int main(int argc, const char* argv[]){

    try{

        hgl::initialize();

        {

            hgl::Window window{"Test Window", 1000, 800, 0, 0};

            // const float vertexBufData[8*3] = {
            //      .5f,  .5f,  .5f,   // 0
            //     -.5f,  .5f,  .5f,   // 1
            //     -.5f, -.5f,  .5f,   // 2
            //      .5f, -.5f,  .5f,   // 3
            //      .5f,  .5f, -.5f,   // 4
            //     -.5f,  .5f, -.5f,   // 5
            //     -.5f, -.5f, -.5f,   // 6
            //      .5f, -.5f, -.5f    // 7
            // };
            // const hgl::LayoutElement dataLayout[1] = {
            //     {hgl::Dim_THREE, hgl::Norm_FALSE}
            // };

            // const unsigned char indexBufData[6*6] = {
            //     0, 1, 3, 1, 3, 2,
            //     1, 0, 5, 0, 5, 4,
            //     6, 5, 7, 5, 7, 4,
            //     2, 3, 6, 3, 6, 7,
            //     0, 3, 4, 3, 4, 7,
            //     2, 1, 6, 1, 6, 5
            // };

            const float data[2*4] = {
                -.5, -.5,
                -.5,  .5,
                 .5, -.5,
                 .5,  .5
            };
            const hgl::LayoutElement dataLayout[1] = {
                {hgl::Dim_TWO, hgl::Norm_FALSE}
            };
            const unsigned char indeces[6] = {0,1,2,1,2,3};

            hgl::VertexArray va;
            hgl::OpenGLBuffer<hgl::VertexBuffer> vb;
            hgl::OpenGLBuffer<hgl::IndexBuffer> ib;
            hgl::Shaders shaders;

            vb.feedData<float>(data, 2*4, hgl::UseStaticDraw);
            ib.feedData<unsigned char>(indeces, 6, hgl::UseStaticDraw);
            va.readBufferData<float>(vb, dataLayout, 1);

            ib.bind();

            shaders.compileString(hgl::VertexShader, vertexShader);
            shaders.compileString(hgl::FragmentShader, fragmentShader);

            shaders.link();
            shaders.validate();

            shaders.bind();

            bool keepRunning = true;
            SDL_Event e;

            while(keepRunning){

                hgl::clear(GL_COLOR_BUFFER_BIT);

                hgl::draw(ib, hgl::DrawTriangles, 6, GL_UNSIGNED_BYTE);

                SDL_GL_SwapWindow(window.getWindow());

                while(SDL_PollEvent(&e)){
                    if(e.type == SDL_QUIT){
                        keepRunning = false;
                        break;
                    }
                }
            
            }

        }

        hgl::quit();
    }
    catch(const std::runtime_error& ex){
        SDL_Log(ex.what());
    }

    return 0;

}