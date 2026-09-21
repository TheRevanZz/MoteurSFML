//
// Created by sylvi on 16/09/2026.
//

#include "CollisionSystem.h"

#include <iostream> 
#include "Game/GameComponentGrid/GameComponentGrid.h"
#include <Class/Core/GameObject/IGameComponent/IGameComponent.h>



void CollisionSystem::compute(const GameComponentGrid& _componentsGrid)
{
    for (const auto& component : *_componentsGrid.GetComponents())
    {
        // DEBUG_ONLY(
        //     std::cout << "COMPONENT 1\n";
        // )

        for (
            auto nearEntities = _componentsGrid.GetNearComponents(component);
            const auto& entity : nearEntities
        )
        {
            // std::cout << "entites proche : " << nearEntities.size() << "\n";

            if (const auto optional_value = entity->GetBounds().findIntersection(component->GetBounds()); 
                optional_value.has_value())
            {
                // std::cout << "test 2\n";
                entity->Collision(component);
                component->Collision(entity);
            }
        }
    }
}