#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

#include "Core/GameObject/IGameComponent/IGameComponent.h"
#include "IUpdateable/IUpdateable.h"

class ShootComponent;

class Bullet : public IGameComponent, public IUpdateable {
public:
    explicit Bullet(sf::Vector2f direction, CoordinateSystem::WorldPoint position,
                    const ShootComponent *shootComponent);

    void update() override;

    void Collision(const std::shared_ptr<IGameComponent> &otherComponent) override;
    
    const sf::Transformable& GetTransformable() const override;
    sf::Transformable& GetTransformable() override;
    
    const sf::FloatRect GetBounds() const override;
    void SetPosition(const CoordinateSystem::WorldPoint& position) override;
    
    const sf::Drawable& GetDrawable() const override;

protected:
    sf::Vector2f _direction;
    float _maxDistance = 200.0f;
    float _currentDistance = 0.f;
    float _speed = 200.0f;

    const ShootComponent *_shootComponent = nullptr;
    
    sf::RectangleShape _shape{{15,5}};
};
