//
// Created by sylvi on 15/09/2026.
//

#pragma once
#include "ILife/ILife.h"

class IDamageable : public ILife
{

protected:
    float _life = 50;
    float _maxLife = 50;

public:
    virtual ~IDamageable() = default;

    virtual void TakeDamage(const float& damage) = 0;
    
    bool IsDead() const { return _life <= 0; }

    [[nodiscard]] const float& GetLife() const override;
    [[nodiscard]] float GetLifePourcent() const override;
    [[nodiscard]] const float& GetMaxLife() const override;
};


