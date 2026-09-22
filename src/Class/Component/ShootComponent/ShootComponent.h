#pragma once
#include "Core/Component/BaseComponent.h"

#include <vector>
class Bullet;
using namespace se3;

class ShootComponent: public BaseComponent
{
    
    friend class Bullet;
public:
    explicit ShootComponent(IGameComponent* owner);
    
    void Shoot();
    
protected:
    std::vector<std::shared_ptr<Bullet>> _bullets = {};
    
    void DeleteBullet(const Bullet* bullet) const;
};  
