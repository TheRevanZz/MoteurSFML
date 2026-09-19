#include "BaseBonus.h"

#include <SFML/System/Time.hpp>

#include "Game/Time/Time.h"
#include "Other/Math/CMath.h"

bool BaseBonus::BonusIsElapsed() const
{
    if (CMath::floatEqual(_life, 0))
        return false;
    return _timer > _life;
}

void BaseBonus::UpdateTimer()
{
    _timer += Time::deltaTime();
}

bool BaseBonus::IsCumulable() const
{
    return _cumulable;
}

const EBonusCategory& BaseBonus::GetBonusCategory() const
{
    return _bonusCategory;
}
