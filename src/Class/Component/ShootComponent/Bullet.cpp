#include "Bullet.h"

#include "ShootComponent.h"
#include "Character/BonusConsumer/BonusConsumer.h"
#include "Game/Time/Time.h"
#include "IBonusConsumer/IBonusConsumer.h"
#include "IBonusGiver/IBonusGiver.h"
#include "IDamageable/IDamageable.h"
#include "IDestructable/IDestructable.h"

Bullet::Bullet(const sf::Vector2f direction, const CoordinateSystem::WorldPoint position,
               const ShootComponent* shootComponent)
    : IGameComponent(), _direction(direction), _shootComponent(shootComponent)
{
    const auto& size = _shape.getGlobalBounds().size;

    _shape.setOrigin({0, size.y / 2});
    Bullet::SetPosition(position);
    const auto player = shootComponent->GetParent();
    _shape.setRotation(player->GetTransformable().getRotation());
    // _transform.setScale({.25f, .1f});
}

void Bullet::update()
{
    const auto& offset = _direction.normalized() * _speed * Time::deltaTime();
    _shape.move(offset);
    _currentDistance += offset.length();

    if (_currentDistance > _maxDistance)
    {
        this->SetMustDie();
    }
}

void Bullet::Collision(const std::shared_ptr<IGameComponent>& otherComponent)
{
    if (const auto owner = _shootComponent->GetParent();
        otherComponent.get() == owner)
        return;

    if (const auto bullet = std::dynamic_pointer_cast<Bullet>(otherComponent); bullet != nullptr)
    {
        return;
    }


    const auto damageable = std::dynamic_pointer_cast<IDamageable>(otherComponent);
    if (damageable != nullptr)
    {
        damageable->TakeDamage(20);
    }

    if (const auto pBonusConsumer = dynamic_cast<const IBonusConsumer*>(_shootComponent->GetParent()); pBonusConsumer !=
        nullptr)
    {
        if (const auto& pBonusGiver = std::dynamic_pointer_cast<IBonusGiver>(otherComponent);
            pBonusGiver != nullptr)
        {
            const auto bonus = pBonusGiver->GetBonus();
            if (bonus != nullptr)
                pBonusConsumer->GetBonusConsumer()->AddBonus(bonus);
        }
    }

    // A damageable object decides itself when it should be destroyed.
    // Destructible objects without health (such as bonus entities) are
    // destroyed directly on impact.
    if (damageable == nullptr)
    {
        if (const auto& destructible = std::dynamic_pointer_cast<IDestructable>(otherComponent))
            destructible->Destruct();
    }

    this->SetMustDie();
}

const sf::Transformable& Bullet::GetTransformable() const
{
    return _shape;
}

sf::Transformable& Bullet::GetTransformable()
{
    return _shape;
}

const sf::FloatRect Bullet::GetBounds() const
{
    return _shape.getGlobalBounds();
}

void Bullet::SetPosition(const CoordinateSystem::WorldPoint& position)
{
    IGameComponent::SetPosition(position);
}

const sf::Drawable& Bullet::getDrawable() const
{
    return _shape;
}
