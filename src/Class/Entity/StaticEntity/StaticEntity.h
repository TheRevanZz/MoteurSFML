//
// Created by evant on 17/09/2026.
//

#pragma once

#include <SFML/Graphics.hpp>

#include "StaticEntityFactory.h"
#include "Entity/BaseEntity/BaseEntity.h"

class BaseBonus;
class StaticEntityFactory;

class StaticEntity : public BaseEntity
{
public:
    static int _count;

    StaticEntity(const sf::Texture &texture, const std::shared_ptr<BaseBonus>& bonus, StaticEntityFactory* factory);
    StaticEntity(const char* texturePath, std::shared_ptr<BaseBonus> bonus, StaticEntityFactory* factory);

    const sf::Sprite &GetSprite() const { return this->_sprite; }
    const int GetId() const { return this->_id; }
    
    sf::Vector2f GetSize() const { return this->_sprite.getLocalBounds().size; }

    sf::Vector2f GetScaledSize() const;

    std::shared_ptr<BaseBonus> GetBonus() const { return this->_bonus; }

    const sf::Vector2f GetPosition() const override { return this->_sprite.getPosition(); }
    const sf::FloatRect GetBounds() const override { return this->_sprite.getGlobalBounds(); }
    const sf::Transform GetTransform() const override { return this->_sprite.getTransform();}

    const sf::Drawable& getDrawable() const override { return this->_sprite; }

    void Collision(const std::shared_ptr<IGameComponent> &otherComponent) override;

    // void setFactory(StaticEntityFactory* pFactory) { _factory = pFactory; }

    sf::Vector2f getPosition() {return this->_sprite.getPosition();}

    void Destroy();

protected:
    CoordinateSystem::WorldPoint _position;
    sf::Vector2u _screenSize;
    int _id = 0;

    std::shared_ptr<BaseBonus> _bonus;

    StaticEntityFactory* _factory;

};

inline int StaticEntity::_count = 0;