//
// Created by sylvi on 16/09/2026.
//

#pragma once
#include <memory>
#include <vector>

#include "Core/Component/BaseComponent.h"

class BaseBonus;

class BonusConsumer : public se3::BaseComponent {

public:
    explicit BonusConsumer(IGameComponent* owner)
        : BaseComponent(owner) {}

    void AddBonus(const std::shared_ptr<BaseBonus>& bonus);
    
    const std::vector<std::shared_ptr<BaseBonus>>& GetBonuses() const;
    void UpdateBonusesTimers();
    
private:
    void RemoveElapsedBonus();

    // const auto& getBonuses() const { return _bonuses; }

protected:
    std::vector<std::shared_ptr<BaseBonus>> _bonuses = {};
};

