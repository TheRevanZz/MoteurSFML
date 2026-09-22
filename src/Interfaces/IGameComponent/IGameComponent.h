//
// Created by sylvi on 14/09/2026.
//

#pragma once
#include <memory>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "Game/CoordinateSystem/CoordinateSystem.h"
#include "IDraweable/IDrawable.h"


class IGameComponent : public IDrawable {

public:
    explicit IGameComponent(const char* texture_path);
    explicit IGameComponent(sf::Texture texture);

    virtual const sf::Vector2f GetPosition() const = 0;
    void SetPosition(const CoordinateSystem::WorldPoint& position);
    virtual const sf::FloatRect& GetBounds() const;
    virtual const sf::Transform GetTransform() const = 0;

    virtual void Collision(const std::shared_ptr<IGameComponent>& otherComponent);
    
protected:
    sf::Texture _mainTexture;
    sf::Sprite _sprite;
    sf::FloatRect _rect;
};



