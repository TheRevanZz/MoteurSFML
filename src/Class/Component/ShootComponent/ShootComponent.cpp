#include "ShootComponent.h"

#include <algorithm>
#include <complex>
#include <cmath>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Bullet.h"
#include "Core/GameplayData/GameplayData.h"
#include "IShooter/IShooter.h"
#include "Game/CoordinateSystem/CoordinateSystem.h"
#include "Game/Time/Time.h"
#

ShootComponent::ShootComponent(IGameComponent* owner)
    : BaseComponent(owner)
{
}

void ShootComponent::Shoot()
{
    const auto parent = GetParent();
    const auto t = parent->GetTransformable();
    const auto rotation = t.getRotation();


    if (
        const auto shooter = dynamic_cast<const IShooter*>(parent);
        shooter != nullptr /*&& _shoot_available > 0u*/
        && (
            GameplayData::GetClock()->getElapsedTime() - _last_shoot_time >
            sf::seconds(static_cast<float>(_shoot_per_second_float)) || _last_shoot_time == sf::Time::Zero
        )
    )
    {
        auto bullet = std::make_shared<Bullet>(
            sf::Vector2f(std::cos(rotation.asRadians()), std::sin(rotation.asRadians())),
            CoordinateSystem::ToWorldPoint(sf::Vector2i(shooter->GetBulletStartPosition())),
            this
        );
        --_shoot_available;
        GameplayData::GetComponentsToAdd()->push_back(std::move(bullet));
        // if (_shoot_available <= 0)
        // {
        //     _on_hold = true;
        //     _last_shoot_time = GameplayData::GetClock()->getElapsedTime();
        //     _elapsed_time = _last_shoot_time.asSeconds();
        // }
        _last_shoot_time = GameplayData::GetClock()->getElapsedTime();
    }
    else if (_shoot_available <= 0u)
    {
        //reload i guess
    }
}

void ShootComponent::Update()
{
    if (_on_hold)
    {
        _elapsed_time += Time::deltaTime();
        if (_elapsed_time /*- _last_shoot_time.asSeconds()*/ >= 1.0f)
        {
            _shoot_available += _shoot_per_second;
            _shoot_available = std::min(_shoot_available, _shoot_per_second);
            _elapsed_time = 0.0f;
        }
    }
}
