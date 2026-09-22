#include "ShootComponent.h"

#include <complex>

#include "Bullet.h"
#include "Core/GameplayData/GameplayData.h"
#include "IShooter/IShooter.h"

ShootComponent::ShootComponent(IGameComponent* owner)
    : BaseComponent(owner)
{
}

void ShootComponent::Shoot()
{
    auto parent = GetParent();
    const auto t = parent->GetSprite();
    const auto rotation = t.getRotation();
    
    if (const auto shooter = dynamic_cast<const IShooter*>(parent); shooter != nullptr)
    {
        auto bullet = std::make_shared<Bullet>(
            sf::Vector2f(std::cos(rotation.asRadians()), std::sin(rotation.asRadians())),
            CoordinateSystem::ToWorldPoint(sf::Vector2i(shooter->GetBulletStartPosition())),
            []()
            {
                // std::cout << "DESTROYED\n";
            }
        );
        GameplayData::GetComponents()->push_back(std::move(bullet));
    }
}
