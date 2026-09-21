//
// Created by sylvi on 15/09/2026.
//

#pragma once
#include "IDestructable/IDestructable.h"


class IDamageable : public IDestructable
{

protected:
    float _life = 50;
    float _maxLife = 50;

public:
    ~IDamageable() override = default;

    virtual void takeDamage(const float& damage) = 0;
    
    bool IsDead() const final  { return _life <= 0; }
};


