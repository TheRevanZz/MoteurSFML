//
// Created by sylvi on 14/09/2026.
//

#pragma once
#include <memory>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "IDraweable/IDrawable.h"

class IGameComponent : public IDrawable {

public:
    virtual const sf::Vector2f getPosition() const = 0;
    virtual const sf::FloatRect getBounds() const = 0;
    virtual const sf::Transform getTransform() const = 0;

    virtual void Collision(const std::shared_ptr<IGameComponent>& otherComponent);
};



