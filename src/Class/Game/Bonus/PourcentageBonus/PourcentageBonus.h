#pragma once
#include "Game/Bonus/BaseBonus/BaseBonus.h"

class PourcentageBonus : public BaseBonus {

public:
    explicit PourcentageBonus(BONUS_CONSTRUCTOR_ARGS)
        : BaseBonus(bonus, bonusCategory ,cumulable) {}

    float GetApplyedBonus(const float value) const override;
};
