//
// Created by sylvi on 16/09/2026.
//

#pragma once
#include <memory>

#include "Enum/EBonusCategory.h"


class BaseBonus;

class BonusConsumer {

public:
    BonusConsumer() = default;

    void addBonus(const std::shared_ptr<BaseBonus>& bonus) {
        _bonuses.push_back(bonus);
    }

    // const auto& getBonuses() const { return _bonuses; }

protected:
    std::vector<std::shared_ptr<BaseBonus>> _bonuses = {
        std::make_shared<PourcentageBonus>(100,EBonusCategory::SPEED,true),
        std::make_shared<DirectBonus>(5,EBonusCategory::SPEED,true)
    };
};

