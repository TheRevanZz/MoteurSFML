#pragma once

#include <memory>

class BonusConsumer;

class IBonusConsumer
{
public:
    [[nodiscard]] virtual const std::shared_ptr<BonusConsumer>& GetBonusConsumer() const = 0;
};
