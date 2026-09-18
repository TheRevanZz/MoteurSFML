//
// Created by evant on 17/09/2026.
//

#pragma once

#include <SFML/Graphics.hpp>

#include "StaticEntityFactory.h"
#include "StaticEntityFactory.h"
#include "Entity/BaseEntity/BaseEntity.h"
#include "Enum/EBonusCategory.h"
using WorldPoint = sf::Vector2f;

class StaticEntityFactory;


class StaticEntity : public BaseEntity
{
public:
    static int _count;

    StaticEntity(const sf::Texture &texture, std::shared_ptr<BaseBonus> bonus, StaticEntityFactory* factory);

    const sf::Sprite &getSprite() const { return this->_sprite; };
    const int getId() const { return this->_id; };

    void setPosition(const WorldPoint &newPosition);

    sf::Vector2f getSize() const { return this->_sprite.getLocalBounds().size; }

    sf::Vector2f getScaledSize() const;

    std::shared_ptr<BaseBonus> getBonus() const { return this->_bonusCategory; }

    const sf::Vector2f getPosition() const override { return this->_sprite.getPosition(); }
    const sf::FloatRect getBounds() const override { return this->_sprite.getGlobalBounds(); }
    const sf::Transform getTransform() const override { return this->_sprite.getTransform();}

    const sf::Drawable& getDrawable() const override { return this->_sprite; }

    void Collision(const std::shared_ptr<IGameComponent> &otherComponent) override;

    // void setFactory(StaticEntityFactory* pFactory) { _factory = pFactory; }

    void destroy();

protected:
    WorldPoint _position;
    sf::Vector2u _screenSize;
    int _id = 0;

    std::shared_ptr<BaseBonus> _bonusCategory;

    StaticEntityFactory* _factory;

};

inline int StaticEntity::_count = 0;