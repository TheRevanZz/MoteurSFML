//
// Created by sylvi on 15/09/2026.
//

#pragma once

#include "Character/BaseCharacter/BaseCharacter.h"
#include "IDestructable/IDestructable.h"

class Ennemy: public BaseCharacter, IDestructable {

public:
    static int _count;

    Ennemy(const sf::Texture& texture, float life);
    
    void TakeDamage(const float& damage) override {}
    
    void update() override {}

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
};

inline int Ennemy::_count = 0;


