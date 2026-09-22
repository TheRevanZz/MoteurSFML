//
// Created by sylvi on 22/09/2026.
//

#pragma once
#include <memory>


class BaseBonus;

class IBonusGiver {

public:
    virtual ~IBonusGiver() = default;

    virtual const std::shared_ptr<BaseBonus>& GetBonus() const = 0;
};


