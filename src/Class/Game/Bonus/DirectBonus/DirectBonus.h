#pragma once
#include "Enum/EBonusCategory.h"
#include "Game/Bonus/BaseBonus/BaseBonus.h"

class DirectBonus : public BaseBonus {

public:
    explicit DirectBonus(BONUS_CONSTRUCTOR_ARGS)
        : BaseBonus(bonus, bonusCategory,cumulable, life) {}

    float GetApplyedBonus(const float value) const override;
};

class DamageBonus : public DirectBonus
{
public:
    explicit DamageBonus(const float bonus, const bool cumulable, const float life)
        : DirectBonus(bonus, EBonusCategory::DAMAGE, cumulable, life) {}
};
