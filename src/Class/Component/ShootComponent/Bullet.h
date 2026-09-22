#pragma once
#include "Core/GameObject/IGameComponent/IGameComponent.h"
#include "IUpdateable/IUpdateable.h"

class Bullet : public IGameComponent, public IUpdateable
{
public:
    explicit Bullet(sf::Vector2f direction,CoordinateSystem::WorldPoint position, void (*onDestroy)());

    void update() override;

    void Collision(const std::shared_ptr<IGameComponent>& otherComponent) override;

    const sf::Drawable& getDrawable() const override;
    const sf::FloatRect GetBounds() const override;
    const sf::Transform GetTransform() const override;
    const sf::Vector2f GetPosition() const override;

protected:
    sf::Vector2f _direction;
    float _maxDistance = 200.0f;
    float _currentDistance = 0.f;
    float _speed = 200.0f;
    void (*_onDestroy)();
};
