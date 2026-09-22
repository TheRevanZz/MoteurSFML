#include "CMath.h"

#include <chrono>
#include <random>

bool CMath::floatEqual(const float a, const float b)
{
    return std::abs(a - b) < 0.001f;
}

float CMath::randf(float min, float max)
{
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(min, max);
    return uniform_dist(e1);
}
