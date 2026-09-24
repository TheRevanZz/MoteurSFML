#pragma once

class ILife
{

public:
    virtual const float& GetLife() const = 0;
    virtual const float& GetMaxLife() const = 0;
    virtual float GetLifePourcent() const = 0;
};
