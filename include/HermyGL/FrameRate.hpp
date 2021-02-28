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
        FrameRate() noexcept(true) = default;
        FrameRate(const FrameRate&) = delete;
        FrameRate(FrameRate&& other) noexcept(true) = default;
        FrameRate& operator= (const FrameRate&) = delete;
        FrameRate& operator= (FrameRate&& other) noexcept(true) = default;
        float operator()() const noexcept(true) { return fps; }
        void compute();
    };
}

#endif