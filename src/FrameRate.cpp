#include "HermyGL/FrameRate.hpp"

namespace hgl{

    void FrameRate::compute(){
        frame++;
        fDur = 
            std::chrono::duration_cast<std::chrono::duration<float, std::ratio<1>>>
            (Clock::now() - frameStart).count();
        if(fDur >= .5f){        // update every half second
            fps = frame/fDur;
            frame = 0;
            frameStart = Clock::now();
        }
    }

}