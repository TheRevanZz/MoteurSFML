//
// Created by evant on 17/09/2026.
//

#include "StaticEntity.h"

#include "Character/BonusConsumer/BonusConsumer.h"
#include "Character/Player/Player.h"
#include "GameWindow/GameWindow.h"
#include  <iostream>
#include <memory>

StaticEntity::StaticEntity(const sf::Texture &texture, std::shared_ptr<BaseBonus> bonus, StaticEntityFactory* factory)
    : BaseEntity(texture), _factory(factory)
{
    _id = _count;
    _sprite.setScale({.15f, .15f});

    // _sprite.setOrigin({_sprite.getGlobalBounds().size.x / 2.f, _sprite.getGlobalBounds().size.y / 2.f});

    setPosition({200, 0});
}

void StaticEntity::setPosition(const WorldPoint& newPosition)
{
    _position = newPosition;
    _sprite.setPosition(sf::Vector2f(GameWindow::toScreenPoint(newPosition, _screenSize)));
}

sf::Vector2f StaticEntity::getScaledSize() const
{
    const auto &scale = this->_sprite.getScale();
    const auto &size = this->_sprite.getLocalBounds().size;

    return {scale.x * size.x, scale.y * size.y};
}

void StaticEntity::Collision(const std::shared_ptr<IGameComponent>& otherComponent)
{
    BaseEntity::Collision(otherComponent);
    std::cout << "ok y'a une collision la\n";
    if (const auto pEntity = std::dynamic_pointer_cast<BonusConsumer>(otherComponent); pEntity != nullptr)
    {
        std::cout << "Static Entity " << this->_id + 1 << " : Collision avec Player" << std::endl;
        destroy();
    }
}

void StaticEntity::destroy()
{
    _factory->deleteStaticEntity(this);
}