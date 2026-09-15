//
// Created by sylvi on 12/09/2026.
//

#include "Player.h"

#include <iostream>

#include "Time/Time.h"

Player::Player(const sf::Texture& texture, const sf::Vector2u& screenSize)
    : _sprite{sf::Sprite(texture)}, _screenSize{screenSize}
{
    _sprite.setScale({.15f, .15f});
    _bounds = _sprite.getLocalBounds();

    _sprite.setOrigin({_bounds.size.x / 2.f, _bounds.size.y / 2.f});
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

void Player::rotate(float angle)
{
    _sprite.rotate(sf::degrees(angle));
}

void Player::progressiveRotate(float targetAngle)
{
    const auto& dt = Time::deltaTime();

    float currentAngle = _sprite.getRotation().asDegrees();
    // pr atteindre le target angle je dois rotate de angle°
    float angle = targetAngle - currentAngle;

    //normalise entre -180 et 180
    while (angle > 180.f)
    {
        angle -= 360.f;
    }
    while (angle < -180.f)
    {
        angle += 360.f;
    }

    float tempRotation = _rotateSpeed * dt;
    if (angle > 0.f)
    {
        if (_rotateSpeed * dt < angle)
            tempRotation = _rotateSpeed * dt;
        else
            tempRotation = angle;

        rotate(tempRotation);
    }
    else if (angle < 0.f)
    {
        if (_rotateSpeed * dt < -angle)
            tempRotation = _rotateSpeed * dt;
        else
            tempRotation = -angle;

        rotate(-tempRotation);
    }

    // std::cout << angle << " : " << _rotateSpeed * dt << std::endl;
}

void Player::update(sf::RenderWindow& window)
{
    handleMovement();
    handleRotation();
    // std::cout << _targetRotation << std::endl;
    progressiveRotate(_targetRotation);
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
     else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        offset.x += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        // Up key pressed.
        offset.y += 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
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

void Player::handleRotation()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        _targetRotation = 180;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        _targetRotation = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        // Up key pressed.
        _targetRotation = 270;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            _targetRotation -= 45.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            _targetRotation += 45.f;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        // Down key pressed.
        _targetRotation = 90;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            _targetRotation += 45.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            _targetRotation -= 45.f;
        }
    }
}