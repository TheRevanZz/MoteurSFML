//
// Created by sylvi on 15/09/2026.
//

#include "IDamageable.h"

const float& IDamageable::GetLife() const
{
    return _life;
}

float IDamageable::GetLifePourcent() const
{
    const float percent = GetLife() / GetMaxLife() * 100.0f;
    return percent;
}

const float& IDamageable::GetMaxLife() const
{
    return _maxLife;
}
