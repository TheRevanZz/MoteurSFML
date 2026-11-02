//
// Created by evant on 24/09/2026.
//

#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Core/Scene/Scene.h"


class GameScene : public Scene
{
public:
    GameScene();

    void start() override;
    void update(float dt) override;
    void Render(sf::RenderWindow& window) override;

protected:
    sf::Texture _backgroundTexture;
    sf::Sprite _backgroundSprite;
    bool _closeGame = false;
};
