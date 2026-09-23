//
// Created by sylvi on 16/09/2026.
//

#include "CollisionSystem.h"

#include <iostream>
#include "Game/GameComponentGrid/GameComponentGrid.h"
#include <Class/Core/GameObject/IGameComponent/IGameComponent.h>

#include "Core/GameplayData/GameplayData.h"


void CollisionSystem::compute(const GameComponentGrid& _componentsGrid)
{
    // for (auto it = _pComponents->begin(); it != _pComponents->end();)
    // {
    //     if (it->get() == pEntity)
    //     {
    //         it = _pComponents->erase(it);
    //     }
    //     else
    //         ++it;
    // }


    // for (const auto& component : *_componentsGrid.GetComponents())
    for (auto it = _componentsGrid.GetComponents()->begin(); it != _componentsGrid.GetComponents()->end();)
    {
        // DEBUG_ONLY(
        //     std::cout << "COMPONENT 1\n";
        // )

        if ((*it)->GetMustDie() == true)
            it = _componentsGrid.GetComponents()->erase(it);
        else
        {
            for (
            auto nearEntities = _componentsGrid.GetNearComponents((*it));
            const auto& entity : nearEntities
        )
            {
                // std::cout << "entites proche : " << nearEntities.size() << "\n";

                if (const auto optional_value = entity->GetBounds().findIntersection((*it)->GetBounds());
                    optional_value.has_value())
                {
                    // std::cout << "test 2\n";
                    entity->Collision((*it));
                    (*it)->Collision(entity);
                }
            }

            ++it;
        }

    }
}
