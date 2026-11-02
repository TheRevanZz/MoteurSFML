//
// Created by evant on 24/09/2026.
//

#pragma once
#include <SFML/Graphics/RenderWindow.hpp>


class Scene
{
public:
    virtual ~Scene() = default;

    virtual void start() = 0;
    virtual void update(float dt) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
};
