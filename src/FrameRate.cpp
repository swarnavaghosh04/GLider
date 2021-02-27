#include "HermyGL/FrameRate.hpp"

namespace hgl{

    void FrameRate::compute(){

        typedef std::chrono::duration<float, std::ratio<1>> Dur;
        
        frame++;
        fDur = 
            (std::chrono::duration_cast<Dur>(Clock::now() - frameStart)).count();
        if(fDur >= .25f){        // update every quarter second
            fps = frame/fDur;
            frame = 0;
            frameStart = Clock::now();
        }
    }

}