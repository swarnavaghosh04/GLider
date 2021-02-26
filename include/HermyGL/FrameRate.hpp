#ifndef HGL_FRAME_RATE__H_
#define HGL_FRAME_RATE__H_

#include <chrono>

namespace hgl{
    class FrameRate{
    private:
        typedef std::chrono::steady_clock Clock;
        Clock::time_point frameStart = Clock::now();
        unsigned int frame=0;
        float fps=60, fDur=1/fps;
    public:
        FrameRate() = default;
        FrameRate(const FrameRate&) = delete;
        FrameRate(FrameRate&& other) = delete;
        FrameRate& operator= (const FrameRate&) = delete;
        FrameRate& operator= (FrameRate&& other) = delete;
        float operator() () const noexcept(true) { return fps; }
        void compute();
    };
}

#endif