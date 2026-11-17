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
        sf::Clock _clock;
        void ProcessEvents();
    
};



