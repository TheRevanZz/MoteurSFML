//
// Created by sylvi on 16/09/2026.
//

#pragma once

#include "GameComponentGrid/GameComponentGrid.h"



class CollisionSystem {

public:
    explicit CollisionSystem() = default;

    void compute(const GameComponentGrid& _componentsGrid);
};
