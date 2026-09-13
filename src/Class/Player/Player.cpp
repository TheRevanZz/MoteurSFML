//
// Created by sylvi on 12/09/2026.
//

#include "Player.h"

#include <iostream>

#include "Time/Time.h"

Player::Player(const sf::Texture& texture, const sf::Vector2u& screenSize)
    : _sprite{sf::Sprite(texture)}, _screenSize{screenSize}
{
    _sprite.setScale({.3f, .3f});
}

void Player::handleEvent(const std::optional<sf::Event>& event)
{
    if (event->is<sf::Event::KeyPressed>())
    {
        auto offset = sf::Vector2f(0, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            offset.x -= 1;
            // Left key pressed.
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            offset.x += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            // Up key pressed.
            offset.y += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            // Down key pressed.
            offset.y -= 1;
        }
        move(offset);
    }
}

void Player::setPosition(const WorldPoint& newPosition)
{
    _position = newPosition;
    _sprite.setPosition(sf::Vector2f(GameWindow::toScreenPoint(newPosition, _screenSize)));
}

sf::Vector2f Player::getScaledSize() const
{
    const auto& scale = this->_sprite.getScale();
    const auto& size = this->_sprite.getLocalBounds().size;

    return {scale.x * size.x, scale.y * size.y};
}

void Player::move(const sf::Vector2f& offset)
{
    //Si offset.length = offset.x c'est équivalent à ce que offset.y soit egal a 0.
    // offset.length c'est Vx**2 + y**2 donc si Vx**2 + y**2 = 0 alors c'est que y = 0 car Vx**2 + 0 = x
    _sprite.move({ offset.x, -offset.y});
}

void Player::update(sf::RenderWindow& window)
{
    handleMovement();
    window.draw(this->_sprite);
}

void Player::handleMovement()
{
    const auto& dt = Time::deltaTime();
    auto offset = sf::Vector2f(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        offset.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        offset.x += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        // Up key pressed.
        offset.y += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        // Down key pressed.
        offset.y -= 1;
    }
    
    if (offset.length() > 0)
    {
        //Le vecteur est normalisé comme ça la valeur de length est toujours égal a 1, donc les déplacements sont toujours de même vitesse
        // même en diagonale
        offset = offset.normalized();
        move(offset * _speed * dt);
    }
}
