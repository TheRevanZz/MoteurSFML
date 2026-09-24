//
// Created by sylvi on 14/09/2026.
//

#include "IGameComponent.h"

#include "Debug.h"
#include "Other/AssetLoader/AssetLoader.h"

#ifndef NDEBUG
    #include <iostream>
#endif


sf::Vector2f IGameComponent::GetPosition() const
{
    return GetTransformable().getPosition();
}

void IGameComponent::SetPosition(const CoordinateSystem::WorldPoint& position)
{
    GetTransformable().setPosition(sf::Vector2f(CoordinateSystem::ToScreenPoint(position)));
}

sf::Transform IGameComponent::GetTransform() const
{
    return GetTransformable().getTransform();
}

void IGameComponent::Collision(const std::shared_ptr<IGameComponent>& otherComponent)
{
    DEBUG_ONLY(
        std::cout << "COLLISION\n";
    )
}
