#pragma once

#include <chrono>

namespace TimeUnit = std::chrono;

class Timer {
public:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    Timer() {
        Reset();
    }

    void Reset() {
        start = Clock::now();
    }

    template <typename Duration = std::chrono::milliseconds>
    Duration Elapsed() const {
        return std::chrono::duration_cast<Duration>(Clock::now() - start);
    }

private:
    TimePoint start;
};

template <typename T>
class Cooldown {
public:
    Cooldown(T delay) : delay(delay), timer() {}
    void Reset() { timer.Reset(); }

    bool Ok() const {
        return timer.Elapsed<T>() >= delay;
    }

private:
    T delay;
    Timer timer;
};
