//
// Created by sylvi on 16/09/2026.
//

#pragma once

class GameComponentGrid;

class CollisionSystem {

public:
    explicit CollisionSystem() = default;

    void compute(const GameComponentGrid& _componentsGrid);
};
