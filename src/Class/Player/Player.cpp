//
// Created by sylvi on 12/09/2026.
//

#include "Player.h"

#include <iostream>
#include <algorithm>
#include <cmath>

#include "Game/Time/Time.h"

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

void Player::update()
{
    handleMovement();
}

void Player::handleMovement()
{
    const float dt = Time::deltaTime();
    
    //calcul forces selon input
    sf::Vector2f input(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        input.x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        input.x += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        input.y += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        input.y -= 1.f;
    }
    
    // calcul forces
    float forceX = 0.f;
    float forceY = 0.f;
    
    if (input.length() > 0.f)
    {
        input = input.normalized();
        
        // application de la force dans la direction indiquee par le joueur
        forceX = input.x * _thrustForce;
        forceY = input.y * _thrustForce;
    }
    
    // euler velocity: v_{n+1} = v_n + (F/m) * dt
    
    // acceleration: a = F / m
    float accelerationX = forceX / _mass;
    float accelerationY = forceY / _mass;
    
    // update velocity
    _velocityX += accelerationX * dt;
    _velocityY += accelerationY * dt;
    
    // deceleration
    // approximation discrète : v(n+1) = friction * v(n)
    // cela simule une diminution exponentielle de la vitesse
    if (input.length() == 0.f)
    {
        _velocityX *= _friction;
        _velocityY *= _friction;
    }
    
    // limitation de la vitesse maximale
    float speed = std::sqrt(_velocityX * _velocityX + _velocityY * _velocityY);
    if (speed > _maxSpeed)
    {
        float scale = _maxSpeed / speed;
        _velocityX *= scale;
        _velocityY *= scale;
    }
    
    // methode d'Euler pour calculer la position :
    // x(n+1) = x(n) + v(n) * dt
    // cela correspond à l'approximation discrète de dx/dt = v
    sf::Vector2f displacement(_velocityX * dt, _velocityY * dt);
    move(displacement);
}
