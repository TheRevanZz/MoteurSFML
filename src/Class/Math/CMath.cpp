#include "CMath.h"

#include <chrono>

bool CMath::floatEqual(const float a, const float b)
{
    return std::abs(a - b) < 0.001f;
}
