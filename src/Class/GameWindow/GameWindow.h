#pragma once


#include <SFML/Graphics.hpp>
#include <string>
#include "CollisionSystem/CollisionSystem.h"


class IGameComponent;
using WorldPoint = sf::Vector2f;
using ScreenPoint = sf::Vector2i;

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
        void show(int width, int height, const std::string& title);

        static ScreenPoint toScreenPoint(const WorldPoint& worldPoint, const sf::Vector2u &screenSize);

        static WorldPoint toWorldPoint(const ScreenPoint& screenPoint,const sf::Vector2u &screenSize);

    private:
        sf::RenderWindow _window;

        std::shared_ptr<Player> _player;
        std::shared_ptr<Player> _player2;
    
        CollisionSystem _collisionSystem;
        sf::Texture _texture;

        sf::Clock _clock;

        std::vector<std::shared_ptr<IGameComponent>> _components = {};

        void processEvents();
        void render();
};

inline ScreenPoint GameWindow::toScreenPoint(const WorldPoint &worldPoint,const sf::Vector2u &screenSize) {
    return {
        static_cast<int>(screenSize.x / 2) + static_cast<int>(worldPoint.x),
        static_cast<int>(screenSize.y) - (static_cast<int>(worldPoint.y) + static_cast<int>(screenSize.y / 2))
    };
}

inline WorldPoint GameWindow::toWorldPoint(const ScreenPoint &screenPoint,const sf::Vector2u &screenSize) {
    return {
        static_cast<float>(screenPoint.x) - static_cast<float>(screenSize.x) / 2.f,
       static_cast<float>(screenSize.y) / 2.f - static_cast<float>(screenPoint.y)
    };
}



