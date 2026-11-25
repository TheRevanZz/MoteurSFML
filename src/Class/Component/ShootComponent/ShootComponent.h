#pragma once
#include <SFML/System/Time.hpp>

#include "Core/Component/BaseComponent.h"

class Bullet;
using namespace se3;

class ShootComponent: public BaseComponent
{
    
    friend class Bullet;
public:
    explicit ShootComponent(IGameComponent* owner);
    
    void Shoot();
    void Update();
    
protected:
    unsigned int _shoot_per_second = 10;    
    float _shoot_per_second_float = 0.1f;
    
    unsigned int _shoot_available = _shoot_per_second;
    float _elapsed_time = 0.0f;
    
    sf::Time _last_shoot_time = sf::Time::Zero;
    
    bool _on_hold = true;
    
};
