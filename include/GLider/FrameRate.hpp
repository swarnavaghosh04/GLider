#ifndef GLI_FRAME_RATE__H_
#define GLI_FRAME_RATE__H_

#include <chrono>

namespace gli{
    class FrameRate{
    private:
        typedef std::chrono::steady_clock Clock;
        Clock::time_point frameStart = Clock::now();
        unsigned int frame=0;
        float fps=60, fDur=1/fps;
    public:
        FrameRate() noexcept = default;
        FrameRate(const FrameRate&) = delete;
        FrameRate(FrameRate&& other) noexcept = default;
        FrameRate& operator= (const FrameRate&) = delete;
        FrameRate& operator= (FrameRate&& other) noexcept = default;
        float operator()() const noexcept { return fps; }
        void compute();
    };
}

#endif