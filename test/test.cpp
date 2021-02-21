#include "HermyGL/HermyGL.hpp"
#include "HermyGL/VertexArray.hpp"
#include "HermyGL/OpenGLBuffer.hpp"
#include <vector>

const char* const vertexShader = R"CODE(
    #version 330 core
    layout(location=0) in vec2 position;
    layout(location=1) in vec3 color;

    out vec3 vertexColor;

    void main(){
        vertexColor = color;
        gl_Position = vec4(position, 0.f, 1.f);
    }
)CODE";

const char* const fragmentShader = R"CODE(
    #version 330 core

    uniform float u_mul;

    in vec3 vertexColor;
    out vec4 FragColor;

    void main(){
        FragColor = vec4(u_mul*vertexColor, 1.f);
    }
)CODE";

int main(int argc, const char* argv[]){

    try{

        hgl::initialize();

        {

            hgl::Window window{"Test Window", 1000, 800, SDL_WINDOW_RESIZABLE, 0};

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
            //     {hgl::D3, hgl::Norm_FALSE}
            // };

            // const unsigned char indexBufData[6*6] = {
            //     0, 1, 3, 1, 3, 2,
            //     1, 0, 5, 0, 5, 4,
            //     6, 5, 7, 5, 7, 4,
            //     2, 3, 6, 3, 6, 7,
            //     0, 3, 4, 3, 4, 7,
            //     2, 1, 6, 1, 6, 5
            // };

            hgl::VertexBufferData<float> vertices = {
                (const float[5*4]){
                    -.5, -.5, 1.f, 0.f, 0.f,
                    -.5,  .5, 0.f, 1.f, 0.f,
                     .5, -.5, 0.f, 0.f, 1.f,
                     .5,  .5, .5f, .5f, .5f
                },
                5*4,
                (const hgl::LayoutElement[2]){
                    {hgl::D2, hgl::Norm_FALSE},
                    {hgl::D3, hgl::Norm_FALSE}
                },
                2
            };

            hgl::BufferData<unsigned char> indices = {
                (const unsigned char[6]){0,1,2,1,2,3},
                6
            };

            hgl::VertexArray va;
            hgl::Buffer<hgl::VertexBuffer> vb;
            hgl::Buffer<hgl::IndexBuffer> ib;
            hgl::Shaders shaders;

            vb.feedData<float>(vertices.data, vertices.dataCount, hgl::UseStaticDraw);
            ib.feedData<unsigned char>(indices.data, indices.dataCount, hgl::UseStaticDraw);
            va.readBufferData<float>(vb, vertices.layout, vertices.layoutCount);

            ib.bind();

            shaders.compileString(hgl::VertexShader, vertexShader);
            shaders.compileString(hgl::FragmentShader, fragmentShader);

            shaders.link();
            shaders.validate();

            
            SDL_Log("Hello\n");

            float u_mul = 0;
            float du_mul = 0.0005;
            shaders.setUniform<float>("u_mul", hgl::D1, u_mul);

            shaders.bind();

            bool keepRunning = true;
            SDL_Event e;

            while(keepRunning){

                hgl::clear(GL_COLOR_BUFFER_BIT);

                u_mul += du_mul;
                shaders.setUniform<float>("u_mul", hgl::D1, u_mul);

                if(u_mul >= 1){
                    u_mul = 1;
                    du_mul *= du_mul<=0?1:-1;
                }else if(u_mul <= 0){
                    u_mul = 0;
                    du_mul *= du_mul>=0?1:-1;
                }

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
    }catch(...){
        SDL_Log("Error Occured\n");
    }

    return 0;

}