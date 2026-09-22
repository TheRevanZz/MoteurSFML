//
// Created by sylvi on 14/09/2026.
//

#include "IGameComponent.h"
#include <utility>
#include "Debug.h"

#ifndef NDEBUG
    #include <iostream>
#endif

IGameComponent::IGameComponent(const char* texture_path)
    : _mainTexture(texture_path), _sprite(_mainTexture), _rect(_sprite.getGlobalBounds())
{
    
}

IGameComponent::IGameComponent(sf::Texture texture)
    : _mainTexture(std::move(texture)), _sprite(_mainTexture), _rect(_sprite.getGlobalBounds())
{
    
}

void IGameComponent::SetPosition(const CoordinateSystem::WorldPoint& position)
{
    _sprite.setPosition(sf::Vector2f(CoordinateSystem::ToScreenPoint(position)));
    _rect = _sprite.getGlobalBounds();
}

const sf::FloatRect& IGameComponent::GetBounds() const
{
    _rect = _sprite.getGlobalBounds();
    return _rect;
}

void IGameComponent::Collision(const std::shared_ptr<IGameComponent>& otherComponent)
{
    DEBUG_ONLY(
        std::cout << "COLLISION\n";    
    )
}
