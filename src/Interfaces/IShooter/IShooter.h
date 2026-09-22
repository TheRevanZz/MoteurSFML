#pragma once
#include "Game/CoordinateSystem/CoordinateSystem.h"

class IShooter
{

public:
    virtual ~IShooter() = default;
    virtual CoordinateSystem::WorldPoint GetBulletStartPosition() const = 0;
    
};
