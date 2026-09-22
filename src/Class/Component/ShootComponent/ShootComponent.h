#pragma once
#include "Core/Component/BaseComponent.h"

class Bullet;
using namespace se3;

class ShootComponent: public BaseComponent
{
    
    friend class Bullet;
public:
    explicit ShootComponent(IGameComponent* owner);
    
    void Shoot();
};
