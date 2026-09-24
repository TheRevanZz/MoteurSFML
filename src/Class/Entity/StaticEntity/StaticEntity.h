//
// Created by evant on 17/09/2026.
//

#pragma once

#include <SFML/Graphics.hpp>

#include "StaticEntityFactory.h"
#include "Entity/BaseEntity/BaseEntity.h"
#include "IBonusGiver/IBonusGiver.h"
#include "IDestructable/IDestructable.h"

class BaseBonus;
class StaticEntityFactory;

class StaticEntity : public BaseEntity, public IBonusGiver, public IDestructable
{
public:
    static int _count;

    StaticEntity(const sf::Texture &texture, const std::shared_ptr<BaseBonus>& bonus);
    StaticEntity(const char* texturePath, std::shared_ptr<BaseBonus> bonus);

    int GetId() const { return this->_id; }
    
    sf::Vector2f GetSize() const { return this->_sprite.getLocalBounds().size; }

    sf::Vector2f GetScaledSize() const;

    const std::shared_ptr<BaseBonus>& GetBonus() const override { return this->_bonus; }
    
    void Collision(const std::shared_ptr<IGameComponent> &otherComponent) override;

    // void setFactory(StaticEntityFactory* pFactory) { _factory = pFactory; }


    void Destruct() override;

protected:
    CoordinateSystem::WorldPoint _position;
    int _id = 0;

    std::shared_ptr<BaseBonus> _bonus;

};

inline int StaticEntity::_count = 0;