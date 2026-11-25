//
// Created by sylvi on 16/09/2026.
//

#pragma once
#include <SFML/Graphics/Rect.hpp>

class IGameComponent;
class GameComponentGrid;

class CollisionSystem {

public:
    explicit CollisionSystem() = default;

    void compute(const GameComponentGrid& _componentsGrid);
    
    static bool IsColliding(const sf::FloatRect& component1, const sf::FloatRect& component2);
};
