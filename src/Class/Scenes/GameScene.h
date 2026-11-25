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
#include "UI/HealthBar/UIHealthBar.h"

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
    std::shared_ptr<UIHealthBar> _healthBar;
    std::shared_ptr<Player> _player = nullptr;
    std::shared_ptr<Player> _player2 = nullptr;

    CollisionSystem _collisionSystem;
    GameComponentGrid _gameComponentGrid;

    sf::Texture _asteroidTexture;

    StaticEntityFactory _staticEntityFactory;
    EnnemyFactory _ennemyFactory;


    std::vector<std::shared_ptr<IGameComponent>> _components = {};
    std::vector<std::shared_ptr<IGameComponent>> _componentsToAdd = {};

    std::vector<std::shared_ptr<se3::UIGameComponent>> _UIComponents = {};

    float _deleteComponentTimer = 0.0f;

    void ProcessEvents();

    static void PreLoadTexture();
    void DeleteComponentsOutOfWindow();
    void AddNewComponents();

    // void UpdateTime();
};