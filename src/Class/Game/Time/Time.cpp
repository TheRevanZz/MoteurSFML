#include "Time.h"

#include <random>

float Time::randf(float min, float max)
{
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(min, max);
    return uniform_dist(e1);
}
