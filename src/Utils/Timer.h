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
    Duration ElapsedRaw() const {
        return std::chrono::duration_cast<Duration>(Clock::now() - start);
    }

    template <typename Duration = std::chrono::milliseconds>
    float Elapsed() const {
        return ElapsedRaw<Duration>().count();
    }

private:
    TimePoint start;
};

template <typename T>
class Cooldown {
public:
    explicit Cooldown(T delay) : delay(delay) {}
    void Reset() { timer.Reset(); }

    bool Ok() const {
        return timer.ElapsedRaw<T>() >= delay;
    }

private:
    T delay;
    Timer timer;
};
