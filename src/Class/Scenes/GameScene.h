//
// Created by evant on 24/09/2026.
//

#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Character/Player/Player.h"
#include "Core/Scene/Scene.h"
#include "Entity/Ennemy/EnnemyFactory.h"
#include "Entity/StaticEntity/StaticEntityFactory.h"
#include "Game/CollisionSystem/CollisionSystem.h"
#include "Game/GameComponentGrid/GameComponentGrid.h"


class GameScene : public Scene
{
public:
    GameScene();

    void start() override;
    void update(float dt) override;
    void Render(sf::RenderWindow& window) override;

protected:
    bool _closeGame = false;



    std::shared_ptr<Player> _player;
    std::shared_ptr<Player> _player2;
    CollisionSystem _collisionSystem;
    GameComponentGrid _gameComponentGrid;

    // à réfléchir
    sf::Texture _asteroidTexture;

    float _deleteComponentTimer = 0.0f;

    StaticEntityFactory _staticEntityFactory;
    EnnemyFactory _ennemyFactory;

    std::vector<std::shared_ptr<IGameComponent>> _components = {};

    void Render();

    void PreLoadTexture();

    void DeleteComponentsOutOfWindow();
};
