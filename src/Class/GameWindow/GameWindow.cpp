#include "GameWindow.h"
#include <iostream>

#include "Player/Player.h"
#include "Macro/Debug.h"
#include "Time/Time.h"


GameWindow::GameWindow() {

    if (!_texture.loadFromFile("ressources/images/spaceship.png")) {
        abort();
    }
    _texture.setSmooth(true);
}

void GameWindow::show(const int width, const int height, const std::string& title)
{
    _window.create(sf::VideoMode(sf::Vector2u(width, height)), title);
    _window.setFramerateLimit(60);
    this->_player = std::make_shared<Player>(_texture, _window.getSize());
    this->_player->setPosition({ - _player->getScaledSize().x / 2.f, _player->getScaledSize().y / 2.f });

    _clock.start();
    
    while (_window.isOpen())
    {
        processEvents();
        auto time = _clock.restart();
        Time::update(time);
        render();
    }
}

void GameWindow::processEvents()
{
    while (const std::optional event = _window.pollEvent())
    {
        if (event->is<sf::Event::Closed>() ||sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            _window.close();

        // _player->handleEvent(event);
    }
}

void GameWindow::render()
{
    // Clear background with White color.
    _window.clear();
    
    _player->update(_window);
    
    DEBUG_ONLY(
       sf::RectangleShape x_line({ 10000.f, 2.f});
       x_line.setFillColor(sf::Color::Red);
       
       x_line.setPosition(sf::Vector2f(toScreenPoint(WorldPoint(0, 0), _window.getSize())));
       sf::RectangleShape y_line({ 10000.f, 2.f});
       y_line.setPosition(sf::Vector2f(toScreenPoint(WorldPoint(0, 0), _window.getSize())));
       y_line.rotate(sf::degrees(-90));
       y_line.setFillColor(sf::Color::Red);

       _window.draw(x_line);
       _window.draw(y_line);
    )
    
    _window.display();
}