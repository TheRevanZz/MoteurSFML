//
// Created by evant on 24/09/2026.
//

#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Core/Scene/Scene.h"
#include "Entity/Ennemy/EnnemyFactory.h"
#include "Entity/StaticEntity/StaticEntityFactory.h"
#include "Game/CollisionSystem/CollisionSystem.h"
#include "Game/GameComponentGrid/GameComponentGrid.h"

class Player;

class GameScene : public Scene
{
public:
    GameScene();

    void start() override;
    void update(float dt) override;
    void Render(sf::RenderWindow& window) override;

protected:
    // sf::Texture _backgroundTexture;
    // sf::Sprite _backgroundSprite;
    bool _closeGame = false;

private:
    std::shared_ptr<Player> _player;
    std::shared_ptr<Player> _player2;

    CollisionSystem _collisionSystem;
    GameComponentGrid _gameComponentGrid;

    StaticEntityFactory _staticEntityFactory;
    EnnemyFactory _ennemyFactory;


    std::vector<std::shared_ptr<IGameComponent>> _components = {};

    float _deleteComponentTimer = 0.0f;

    sf::Texture _asteroidTexture;

    static void PreLoadTexture();
    void DeleteComponentsOutOfWindow();
};
