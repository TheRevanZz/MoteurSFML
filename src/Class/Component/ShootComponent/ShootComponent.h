#pragma once
#include "Core/Component/BaseComponent.h"

using namespace se3;

class ShootComponent: public BaseComponent
{
public:
    explicit ShootComponent(IGameComponent* owner);
    
    void Shoot();
    
};  
