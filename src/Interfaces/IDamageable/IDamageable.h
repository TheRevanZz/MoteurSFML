//
// Created by sylvi on 15/09/2026.
//

#pragma once

class IDamageable
{

protected:
    float _life = 50;
    float _maxLife = 50;

public:
    virtual ~IDamageable() = default;

    virtual void TakeDamage(const float& damage) = 0;
    
    bool IsDead() const { return _life <= 0; }
};


