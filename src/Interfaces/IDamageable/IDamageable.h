//
// Created by sylvi on 15/09/2026.
//

#pragma once



class IDamageable {

protected:
    int _life = 50;
    int _maxLife = 50;

public:
    virtual ~IDamageable() = default;

    virtual void takeDamage(const int& damage) = 0;
};


