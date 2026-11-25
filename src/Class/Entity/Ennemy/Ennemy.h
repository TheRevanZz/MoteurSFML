//
// Created by sylvi on 15/09/2026.
//

#pragma once

#include "Character/BaseCharacter/BaseCharacter.h"
#include "IDestructable/IDestructable.h"
#include "IShooter/IShooter.h"

class ShootComponent;

class Ennemy: public BaseCharacter, public IDestructable, public IShooter {

public:
    static int _count;

    Ennemy(const sf::Texture& texture, float life);
    
    void TakeDamage(const float& damage) override;
    
    void update() override;

    CoordinateSystem::WorldPoint GetBulletStartPosition() const override;

    void Shoot();

    int GetId() const { return this->_id; }

    sf::Vector2f GetSize() const { return this->_sprite.getLocalBounds().size; }

    sf::Vector2f GetScaledSize() const;

    void Collision(const std::shared_ptr<IGameComponent> &otherComponent) override;

    // void setFactory(StaticEntityFactory* pFactory) { _factory = pFactory; }


    void Destruct() override;

protected:
    CoordinateSystem::WorldPoint _position;
    int _id = 0;

    std::shared_ptr<BaseBonus> _bonus;
    std::shared_ptr<ShootComponent> _pShootComponent;
    sf::Clock _shootClock;
};

inline int Ennemy::_count = 0;

