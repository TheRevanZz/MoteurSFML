#include "GameWindow.h"
#include <iostream>
#include <ranges>

#include "Character/Player/Player.h"
#include "Core/GameplayData/GameplayData.h"
#include "Core/Scene/SceneManager.h"
#include "Macro/Debug.h"
#include "Game/Time/Time.h"
#include "Game/WindowData/WindowData.h"
#include "Other/AssetLoader/AssetLoader.h"


GameWindow::GameWindow()
{
}

void GameWindow::Show(const int width, const int height, const std::string& title)
{
    _window.create(sf::VideoMode(sf::Vector2u(width, height)), title);
    _window.setFramerateLimit(60);
    WindowData::SetWindow(&_window);
    
    _clock.start();
    float dt = 0.f;
    
    while (_window.isOpen())
    {
        ProcessEvents();

        auto time = _clock.restart();
        dt = time.asSeconds();

        Time::update(time);

        SceneManager::getInstance().update(dt);

        _window.clear();
        SceneManager::getInstance().render(_window);
        _window.display();
    }
}

void GameWindow::ProcessEvents()
{
    while (const std::optional event = _window.pollEvent())
    {
        if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            _window.close();
    }
}