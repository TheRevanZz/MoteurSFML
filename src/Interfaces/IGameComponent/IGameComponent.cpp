//
// Created by sylvi on 14/09/2026.
//

#include "IGameComponent.h"
#include <iostream>

#include "Debug.h"

void IGameComponent::Collision(const std::shared_ptr<IGameComponent>& otherComponent)
{
    DEBUG_ONLY(
        std::cout << "COLLISION\n";    
    )
}
