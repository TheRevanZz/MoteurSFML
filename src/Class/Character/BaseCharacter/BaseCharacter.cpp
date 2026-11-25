//
// Created by sylvi on 15/09/2026.
//

#include "BaseCharacter.h"

#include <algorithm>
#include <cmath>

#include "Game/Time/Time.h"
#include "Game/WindowData/WindowData.h"
#include "Other/AssetLoader/AssetLoader.h"

BaseCharacter::BaseCharacter(sf::Texture texture, const float life) 
    : _mainTexture(std::move(texture)), _sprite(_mainTexture)
{
    _life = life;
    _maxLife = life;
}

BaseCharacter::BaseCharacter(const char* texture_path, const float life)
    : _mainTexture(AssetLoader::LoadAndGetTexture(texture_path)), _sprite(_mainTexture)
{
    _life = life;
    _maxLife = life;
}

sf::Transformable& BaseCharacter::GetTransformable()
{
    return _sprite;
}

const sf::Transformable& BaseCharacter::GetTransformable() const
{
    return _sprite;
}

const sf::FloatRect BaseCharacter::GetBounds() const
{
    return _sprite.getGlobalBounds();
}

const sf::Drawable& BaseCharacter::GetDrawable() const
{
    return _sprite;
}

sf::Vector2f BaseCharacter::ApplyPhysics(
    const sf::Vector2f& input,
    const float deltaTime,
    const float maxSpeed,
    const sf::Vector2f& additionalForce)
{
    sf::Vector2f direction = input;
    if (direction.length() > 0.f)
        direction = direction.normalized();

    const sf::Vector2f force = direction * _thrustForce + additionalForce;
    _velocityX += force.x / _mass * deltaTime;
    _velocityY += force.y / _mass * deltaTime;

    if (input.length() == 0.f && additionalForce.length() == 0.f)
    {
        _velocityX *= _friction;
        _velocityY *= _friction;
    }

    const float speed = std::sqrt(_velocityX * _velocityX + _velocityY * _velocityY);
    if (speed > maxSpeed)
    {
        const float scale = maxSpeed / speed;
        _velocityX *= scale;
        _velocityY *= scale;
    }

    return {_velocityX * deltaTime, _velocityY * deltaTime};
}

void BaseCharacter::Move(const sf::Vector2f& offset)
{
    _sprite.move({offset.x, -offset.y});

    auto position = _sprite.getPosition();
    const auto size = _sprite.getLocalBounds().size;
    const auto scale = _sprite.getScale();
    const sf::Vector2f halfSize(size.x * scale.x / 2.f, size.y * scale.y / 2.f);
    const auto screenSize = WindowData::GetScreenSize();

    if (position.x > screenSize.x - halfSize.x)
    {
        position.x = screenSize.x - halfSize.x;
        if (_velocityX > 0.f)
            _velocityX = -_velocityX;
    }
    if (position.x < halfSize.x)
    {
        position.x = halfSize.x;
        if (_velocityX < 0.f)
            _velocityX = -_velocityX;
    }
    if (position.y > screenSize.y - halfSize.y)
    {
        position.y = screenSize.y - halfSize.y;
        if (_velocityY < 0.f)
            _velocityY = -_velocityY;
    }
    if (position.y < halfSize.y)
    {
        position.y = halfSize.y;
        if (_velocityY > 0.f)
            _velocityY = -_velocityY;
    }

    _sprite.setPosition(position);
}

void BaseCharacter::Rotate(const float angle)
{
    _sprite.rotate(sf::degrees(angle));
}

void BaseCharacter::ProgressiveRotate(const float targetAngle)
{
    const float dt = Time::deltaTime();
    const float currentAngle = _sprite.getRotation().asDegrees();
    float angle = targetAngle - currentAngle;

    while (angle > 180.f)
        angle -= 360.f;
    while (angle < -180.f)
        angle += 360.f;

    if (angle > 0.f)
        Rotate(std::min(_rotateSpeed * dt, angle));
    else if (angle < 0.f)
        Rotate(-std::min(_rotateSpeed * dt, -angle));
}

bool BaseCharacter::IsMoving() const
{
    constexpr float minimumSpeed = 1.f;
    return _velocityX * _velocityX + _velocityY * _velocityY > minimumSpeed * minimumSpeed;
}

void BaseCharacter::StopMovement()
{
    _velocityX = 0.f;
    _velocityY = 0.f;
}
