#pragma once


#include <SFML/Graphics.hpp>
#include <string>

#include "Entity/Ennemy/EnnemyFactory.h"
#include "Entity/StaticEntity/StaticEntityFactory.h"
#include "Game/CollisionSystem/CollisionSystem.h"
#include "Game/GameComponentGrid/GameComponentGrid.h"
#include "Game/WindowData/WindowData.h"

class Player;

class GameWindow
{
    
    public:
        GameWindow();

        // Show window.
        // Input:
        //  * width: window width (pixels).
        //  * height: window height (pixels).
        //  * title: window title.
        // Output:
        //  * Nothing.
        void Show(int width, int height, const std::string& title);

    private:
        sf::RenderWindow _window;

        std::shared_ptr<Player> _player;
        std::shared_ptr<Player> _player2;
        CollisionSystem _collisionSystem;
        GameComponentGrid _gameComponentGrid;
        EnnemyFactory _ennemyFactory;
    
        // à réfléchir
        sf::Texture _asteroidTexture;

        float _deleteComponentTimer = 0.0f;

        StaticEntityFactory _staticEntityFactory;

        sf::Clock _clock;

        std::vector<std::shared_ptr<IGameComponent>> _components = {};

        void ProcessEvents();
        void Render();
    
        void PreLoadTexture();
    
        void DeleteComponentsOutOfWindow();
    
};



