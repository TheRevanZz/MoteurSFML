#include "DirectBonus.h"

#include <algorithm>

float DirectBonus::GetApplyedBonus(const float value) const
{
    return std::max(value + _bonus,0.f);
}
