#include "Bullet.h"

#include "Core/GameplayData/GameplayData.h"
#include "Game/Time/Time.h"
#include "IDamageable/IDamageable.h"


Bullet::Bullet(const sf::Vector2f direction, const CoordinateSystem::WorldPoint position, void(* onDestroy)())
    : IGameComponent("ressources/images/aoba.png"), _direction(direction), _onDestroy(onDestroy)
{
    SetPosition(position);
    _sprite.setScale({.25f, .1f});
}

void Bullet::update()
{
    const auto& offset = _direction.normalized() * _speed * Time::deltaTime();
    _sprite.move(offset);
    _currentDistance += offset.length();

    if (_currentDistance > _maxDistance)
    {
       _onDestroy();
    }
}

void Bullet::Collision(const std::shared_ptr<IGameComponent>& otherComponent)
{
    if (
        const auto& damageable = std::dynamic_pointer_cast<IDamageable>(otherComponent);
        damageable != nullptr
    )
    {
        damageable->takeDamage(20);
        
        _onDestroy();
    }
}

const sf::Drawable& Bullet::getDrawable() const
{
    return _sprite;
}

const sf::FloatRect Bullet::GetBounds() const
{
    return _sprite.getGlobalBounds();
}

const sf::Transform Bullet::GetTransform() const
{
    return _sprite.getTransform();
}

const sf::Vector2f Bullet::GetPosition() const
{
    return _sprite.getPosition();
}
