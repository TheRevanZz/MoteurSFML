//
// Created by sylvi on 14/09/2026.
//

#include "IGameComponent.h"
#include <iostream>

#include "Debug.h"

IGameComponent::IGameComponent(const sf::Texture& texture)
    : _sprite(texture)
{
}

void IGameComponent::Collision(const std::shared_ptr<IGameComponent>& otherComponent) const
{
    DEBUG_ONLY(
        std::cout << "COLLISION\n";    
    )
}
