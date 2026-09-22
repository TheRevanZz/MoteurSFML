#include "Bullet.h"

#include "ShootComponent.h"
#include "Character/BonusConsumer/BonusConsumer.h"
#include "Core/GameplayData/GameplayData.h"
#include "Game/Time/Time.h"
#include "IBonusConsumer/IBonusConsumer.h"
#include "IBonusGiver/IBonusGiver.h"
#include "IDamageable/IDamageable.h"

Bullet::Bullet(sf::Vector2f direction, CoordinateSystem::WorldPoint position, const ShootComponent *shootComponent,
               IGameComponent *owner)
    : IGameComponent("ressources/images/aoba.png"), _direction(direction), _shootComponent(shootComponent),
      _owner(owner) {
    SetPosition(position);
    _sprite.setScale({.25f, .1f});
}

void Bullet::update() {
    const auto &offset = _direction.normalized() * _speed * Time::deltaTime();
    _sprite.move(offset);
    _currentDistance += offset.length();

    if (_currentDistance > _maxDistance) {
        _shootComponent->DeleteBullet(this);
    }
}

void Bullet::Collision(const std::shared_ptr<IGameComponent> &otherComponent) {
    if (
        const auto &damageable = std::dynamic_pointer_cast<IDamageable>(otherComponent);
        damageable != nullptr
    ) {
        damageable->takeDamage(20);

        _shootComponent->DeleteBullet(this);
    }

    if (const auto pBonusConsumer = dynamic_cast<IBonusConsumer*>(_owner)) {
        if (const auto &pBonusGiver = std::dynamic_pointer_cast<IBonusGiver>(otherComponent);
            pBonusGiver != nullptr) {

            const auto bonus = pBonusGiver->GetBonus();
            if (bonus != nullptr)
                pBonusConsumer->GetBonusConsumer()->AddBonus(bonus);
        }
    }

    if (const auto& destructible = std::dynamic_pointer_cast<IDestructable>(otherComponent)) {
        destructible->Destruct();
    }
}

const sf::Drawable &Bullet::getDrawable() const {
    return _sprite;
}

const sf::FloatRect Bullet::GetBounds() const {
    return _sprite.getGlobalBounds();
}

const sf::Transform Bullet::GetTransform() const {
    return _sprite.getTransform();
}

const sf::Vector2f Bullet::GetPosition() const {
    return _sprite.getPosition();
}
