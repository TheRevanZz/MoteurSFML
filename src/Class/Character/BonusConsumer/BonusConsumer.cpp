//
// Created by sylvi on 16/09/2026.
//

#include "BonusConsumer.h"

#include "Game/Bonus/BaseBonus/BaseBonus.h"
#include "Game/Bonus/DirectBonus/DirectBonus.h"
#include "IDamageable/IDamageable.h"
#include "Core/GameObject/IGameComponent/IGameComponent.h"


void BonusConsumer::AddBonus(const std::shared_ptr<BaseBonus>& bonus)
{
    _bonuses.push_back(bonus);
}

const std::vector<std::shared_ptr<BaseBonus>>& BonusConsumer::GetBonuses() const
{
    return _bonuses;
}

void BonusConsumer::UpdateBonusesTimers()
{
    for (const auto& bonus : _bonuses)
        bonus->UpdateTimer();
    RemoveElapsedBonus();
}

void BonusConsumer::RemoveElapsedBonus()
{
    for (auto it = _bonuses.begin(); it != _bonuses.end();)
    {
        if ((*it)->IsElapsed())
        {
            it = _bonuses.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
