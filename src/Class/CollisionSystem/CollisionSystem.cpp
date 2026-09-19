//
// Created by sylvi on 16/09/2026.
//

#include "CollisionSystem.h"

#include <iostream> 
#include <SFML/Graphics/RectangleShape.hpp>
#include <IGameComponent/IGameComponent.h>
#include "Debug.h"



void CollisionSystem::compute(const GameComponentGrid& _componentsGrid)
{
    for (const auto& component : *_componentsGrid.getComponents())
    {
        // DEBUG_ONLY(
        //     std::cout << "COMPONENT 1\n";
        // )

        for (
            auto nearEntities = _componentsGrid.getNearComponents(component);
            const auto& entity : nearEntities
        )
        {
            if (const auto optional_value = entity->getBounds().findIntersection(component->getBounds()); 
                optional_value.has_value())
            {
                entity->Collision(component);
                component->Collision(entity);
            }
        }
    }
}