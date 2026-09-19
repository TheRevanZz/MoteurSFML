#include "DirectBonus.h"

float DirectBonus::GetApplyedBonus(const float value) const
{
    return value + _bonus;
}
