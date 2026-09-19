#include "PourcentageBonus.h"

float PourcentageBonus::GetApplyedBonus(const float value) const
{
    return value * (1 + _bonus / 100);
}
