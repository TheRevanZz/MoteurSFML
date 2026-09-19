#pragma once
#include "Game/Bonus/BaseBonus/BaseBonus.h"

class DirectBonus : public BaseBonus {

public:
    explicit DirectBonus(BONUS_CONSTRUCTOR_ARGS)
        : BaseBonus(bonus, bonusCategory, cumulable, life) {}

    float GetApplyedBonus(const float value) const override;
};
