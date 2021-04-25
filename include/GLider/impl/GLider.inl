#ifndef GLIDER__I_
#define GLIDER__I_

#include "GLider/GLider.hpp"

namespace gli{

    inline void initialize(int major, int minor){

        constexpr const SDLAttributeArray<5> SDL_defaultAttributes{
            std::pair{SDL_GL_DOUBLEBUFFER, 1},
            std::pair{SDL_GL_DEPTH_SIZE, 32},
            std::pair{SDL_GL_MULTISAMPLEBUFFERS, 1},
            std::pair{SDL_GL_MULTISAMPLESAMPLES, 4},
            std::pair{SDL_GL_ACCELERATED_VISUAL, 1}
        };
        
        initialize(major, minor, SDL_defaultAttributes);
    }

    template<std::size_t N>
    void initialize(int major, int minor, const SDLAttributeArray<N>& attributes){

        initialize_base(major,minor, [&](int& errorVal){
            for(const std::pair<SDL_GLattr, int>& p : attributes)
                errorVal += SDL_GL_SetAttribute(p.first, p.second);
        });

    }

}

#endif
