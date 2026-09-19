//
// Created by sylvi on 16/09/2026.
//

#include "BonusConsumer.h"

void BonusConsumer::AddBonus(const std::shared_ptr<BaseBonus>& bonus)
{
    _bonuses.push_back(bonus);
}

void BonusConsumer::RemoveBonus(const BaseBonus* bonus)
{
    for (auto it = _bonuses.begin(); it != _bonuses.end();)
    {
        if (it->get() == bonus)
        {
            it = _bonuses.erase(it);
        }
        ++it;
    }
}
