//
// Created by sylvi on 14/09/2026.
//

#include "IGameComponent.h"
#include <iostream>

#include "Debug.h"

IGameComponent::IGameComponent(const char* texture_path)
    : _mainTexture(texture_path), _sprite(_mainTexture)
{
}

IGameComponent::IGameComponent(sf::Texture texture)
    : _mainTexture(std::move(texture)), _sprite(_mainTexture)
{
}

void IGameComponent::Collision(const std::shared_ptr<IGameComponent>& otherComponent) const
{
    DEBUG_ONLY(
        std::cout << "COLLISION\n";    
    )
}
