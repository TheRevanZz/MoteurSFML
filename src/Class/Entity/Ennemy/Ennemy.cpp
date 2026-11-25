//
// Created by sylvi on 15/09/2026.
//

#include "Ennemy.h"

#include <algorithm>
#include <cmath>
#include <limits>

#include "Character/Player/Player.h"
#include "Core/GameplayData/GameplayData.h"
#include "Game/Time/Time.h"
#include "Game/WindowData/WindowData.h"
#include "Other/Math/CMath.h"

Ennemy::Ennemy(const sf::Texture &texture, const float life)
    : BaseCharacter(texture, life)
{
    _sprite.setScale({.15f, .15f});
    const auto localBounds = _sprite.getLocalBounds();
    _sprite.setOrigin({
        localBounds.position.x + localBounds.size.x / 2.f,
        localBounds.position.y + localBounds.size.y / 2.f
    });

    float xpos = CMath::randf(-(static_cast<int>(WindowData::GetScreenSize().x / 2)), static_cast<int>(WindowData::GetScreenSize().x / 2 - _sprite.getGlobalBounds().size.x));
    float ypos = CMath::randf(-(static_cast<int>(WindowData::GetScreenSize().y / 2 - _sprite.getGlobalBounds().size.y)), static_cast<int>(WindowData::GetScreenSize().y / 2));

    _id = _count;

    // SetPosition({static_cast<float>(std::rand()%WindowData::GetScreenSize().x), static_cast<float>(std::rand()%WindowData::GetScreenSize().y)});
    SetPosition({xpos, ypos});
    _count++;
}

sf::Vector2f Ennemy::GetScaledSize() const
{
    const auto& scale = this->_sprite.getScale();
    const auto& size = this->_sprite.getLocalBounds().size;

    return {scale.x * size.x, scale.y * size.y};
}

void Ennemy::update()
{
    auto* components = GameplayData::GetComponents();
    if (components == nullptr)
        return;

    std::shared_ptr<Player> target;
    float nearestDistanceSquared = std::numeric_limits<float>::max();
    const auto enemyBounds = GetBounds();
    const sf::Vector2f enemyCenter(
        enemyBounds.position.x + enemyBounds.size.x / 2.f,
        enemyBounds.position.y + enemyBounds.size.y / 2.f
    );

    for (const auto& component : *components)
    {
        const auto player = std::dynamic_pointer_cast<Player>(component);
        if (!player)
            continue;

        const auto playerBounds = player->GetBounds();
        const float dx = playerBounds.position.x + playerBounds.size.x / 2.f - enemyCenter.x;
        const float dy = playerBounds.position.y + playerBounds.size.y / 2.f - enemyCenter.y;
        const float distanceSquared = dx * dx + dy * dy;
        if (distanceSquared < nearestDistanceSquared)
        {
            nearestDistanceSquared = distanceSquared;
            target = player;
        }
    }

    if (!target)
    {
        Move(ApplyPhysics({}, Time::deltaTime(), _maxSpeed));
        return;
    }

    const auto targetBounds = target->GetBounds();
    const sf::Vector2f targetCenter(
        targetBounds.position.x + targetBounds.size.x / 2.f,
        targetBounds.position.y + targetBounds.size.y / 2.f
    );
    const float deltaX = targetCenter.x - enemyCenter.x;
    const float deltaY = enemyCenter.y - targetCenter.y;
    if (deltaX != 0.f || deltaY != 0.f)
    {
        const float screenDeltaY = -deltaY;
        _targetRotation = std::atan2(screenDeltaY, deltaX) * 180.f / std::numbers::pi_v<float>;
        ProgressiveRotate(_targetRotation);
    }

    const float enemyRadius = std::hypot(enemyBounds.size.x, enemyBounds.size.y) / 2.f;
    const float targetRadius = std::hypot(targetBounds.size.x, targetBounds.size.y) / 2.f;
    constexpr float minimumGap = 10.f;
    const float minimumDistance = enemyRadius + targetRadius + minimumGap;
    const float distance = std::hypot(deltaX, deltaY);

    if (!target->IsMoving())
    {
        const sf::Vector2f towardTarget = distance > 0.f
            ? sf::Vector2f(deltaX / distance, deltaY / distance)
            : sf::Vector2f(1.f, 0.f);
        const sf::Vector2f tangent(-towardTarget.y, towardTarget.x);
        const float orbitDistance = minimumDistance + 20.f;
        const float radialCorrection = std::clamp(
            (distance - orbitDistance) / orbitDistance,
            -1.f,
            1.f
        );
        const sf::Vector2f orbitDirection = tangent + towardTarget * radialCorrection;
        Move(ApplyPhysics(orbitDirection, Time::deltaTime(), _maxSpeed));
        return;
    }

    if (distance <= minimumDistance)
    {
        StopMovement();
        return;
    }

    const sf::Vector2f direction(
        deltaX,
        deltaY
    );
    Move(ApplyPhysics(direction, Time::deltaTime(), _maxSpeed));
}

void Ennemy::Collision(const std::shared_ptr<IGameComponent>& otherComponent)
{
    BaseCharacter::Collision(otherComponent);
}

void Ennemy::Destruct()
{
    SetMustDie();
}
