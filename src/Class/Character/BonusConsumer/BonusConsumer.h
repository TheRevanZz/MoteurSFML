//
// Created by sylvi on 16/09/2026.
//

#pragma once
#include <memory>
#include <vector>

class BaseBonus;

class BonusConsumer {

public:
    BonusConsumer() = default;

    void AddBonus(const std::shared_ptr<BaseBonus>& bonus);
    
    void UpdateBonusesTimers();
    
private:
    void RemoveElapsedBonus();

    // const auto& getBonuses() const { return _bonuses; }

protected:
    std::vector<std::shared_ptr<BaseBonus>> _bonuses = {};
};

