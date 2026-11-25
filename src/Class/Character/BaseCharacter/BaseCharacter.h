//
// Created by sylvi on 15/09/2026.
//
#pragma once
#include <SFML/Graphics.hpp>

#include "IDamageable/IDamageable.h"
#include "Class/Core/GameObject/IGameComponent/IGameComponent.h"
#include "IUpdateable/IUpdateable.h"

class BaseBonus;

namespace sf
{
    class Texture;
}

class BaseCharacter :
    public IGameComponent,
    public IUpdateable,
    public IDamageable
{
public:
    BaseCharacter(sf::Texture texture, float life);
    BaseCharacter(const char* texture_path, float life);
    
    sf::Transformable& GetTransformable() override;
    const sf::Transformable& GetTransformable() const override;
    const sf::FloatRect GetBounds() const override;
    const sf::Drawable& GetDrawable() const override;
    void Move(const sf::Vector2f& offset);
    void Rotate(float angle);
    void ProgressiveRotate(float targetAngle);
    bool IsMoving() const;
    void StopMovement();

protected:    
    sf::Texture _mainTexture;
    sf::Sprite _sprite;

    sf::Vector2f ApplyPhysics(
        const sf::Vector2f& input,
        float deltaTime,
        float maxSpeed,
        const sf::Vector2f& additionalForce = {}
    );

    float _velocityX = 0.f;
    float _velocityY = 0.f;
    float _mass = 1.f;
    float _maxSpeed = 150.f;
    float _friction = 0.90f;
    float _thrustForce = 500.f;
    float _rotateSpeed = 500.f;
    float _targetRotation = 0.f;
};
