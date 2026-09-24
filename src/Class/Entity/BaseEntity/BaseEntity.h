//
// Created by evant on 17/09/2026.
//

#pragma once
#include "Class/Core/GameObject/IGameComponent/IGameComponent.h"

#include <SFML/Graphics/Sprite.hpp>

class BaseEntity :
    public IGameComponent
{
public:
    explicit BaseEntity(const sf::Texture& texture);
    explicit BaseEntity(const char* texturePath);
    
    const sf::Transformable& GetTransformable() const override;
    sf::Transformable& GetTransformable() override;
    const sf::Drawable& getDrawable() const override;
    const sf::FloatRect GetBounds() const override;

    
protected: 
    sf::Texture _mainTexture;
    sf::Sprite _sprite;
};
