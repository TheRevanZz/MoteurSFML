//
// Created by sylvi on 14/09/2026.
//

#pragma once
#include <memory>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "IDraweable/IDrawable.h"

class IGameComponent : public IDrawable {

public:
    
    IGameComponent(const char* texture_path);
    IGameComponent(sf::Texture texture);

    virtual const sf::Vector2f getPosition() const = 0;
    virtual const sf::FloatRect getBounds() const = 0;
    virtual const sf::Transform getTransform() const = 0;

    virtual void Collision(const std::shared_ptr<IGameComponent>& otherComponent);
    
protected:
    sf::Texture _mainTexture;
    sf::Sprite _sprite;
};



