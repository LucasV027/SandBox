#pragma once

#include <random>

namespace Random {
    inline std::mt19937& GetEngine() {
        static std::random_device rd;
        static std::mt19937 engine(rd());
        return engine;
    }

    inline bool Flip() {
        static std::bernoulli_distribution dist(0.5);
        return dist(GetEngine());
    }

    inline double Random() {
        static std::uniform_real_distribution<double> dist(0.0, 1.0);
        return dist(GetEngine());
    }
}
