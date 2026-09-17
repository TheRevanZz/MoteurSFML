//
// Created by evant on 17/09/2026.
//

#include "StaticEntity.h"

#include "GameWindow/GameWindow.h"

StaticEntity::StaticEntity(const sf::Texture &texture, const sf::Vector2u &screenSize, std::shared_ptr<BaseBonus> bonus)
    : BaseEntity(texture)
{
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
