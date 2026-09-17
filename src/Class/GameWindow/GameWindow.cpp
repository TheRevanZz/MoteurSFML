#include "GameWindow.h"
#include <iostream>

#include "Character/Player/Player.h"
#include "Macro/Debug.h"
#include "Game/Time/Time.h"
#include "Game/WindowData/WindowData.h"


GameWindow::GameWindow() {

    if (!_texture.loadFromFile("ressources/images/spaceship_3.png")) {
        abort();
    }
    _texture.setSmooth(true);
}

void GameWindow::show(const int width, const int height, const std::string& title)
{
    _window.create(sf::VideoMode(sf::Vector2u(width, height)), title);
    _window.setFramerateLimit(60);
    WindowData::setWindow(&_window);
    
    this->_player = std::make_shared<Player>(_texture);
    this->_player->setPosition({ - _player->getScaledSize().x / 2.f, _player->getScaledSize().y / 2.f });
    
    
    this->_player2 = std::make_shared<Player>(_texture);
    this->_player2->setPosition({ -100, -100});
    if (this->_player2->ChangeKey(EActionTag::UP, sf::Keyboard::Key::Num0))
    {
        
    }

    _components = { _player, _player2};
    _collisionSystem.setComponents(_components);
    _clock.start();
    
    while (_window.isOpen())
    {
        processEvents();
        auto time = _clock.restart();
        Time::update(time);
        // std::cout << 1 / time.asSeconds() << std::endl;
        render();
    }
}

void GameWindow::processEvents()
{
    while (const std::optional event = _window.pollEvent())
    {
        if (event->is<sf::Event::Closed>() ||sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            _window.close();
    }
}

void GameWindow::render()
{
    // Clear background with White color.
    _window.clear();

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
    
    for (const auto& component : _components) {
        if (auto* UpdateableCompoent = dynamic_cast<IUpdateable*>(component.get()); UpdateableCompoent != nullptr) {
            UpdateableCompoent->update();
        }
        _window.draw(component->getDrawable());
        DEBUG_ONLY(
            sf::RectangleShape bounds(sf::Vector2f(component->getBounds().size.x, component->getBounds().size.y));
            bounds.setPosition(component->getPosition());
            bounds.setFillColor(sf::Color::Transparent);
            bounds.setOutlineThickness(4.f);
            bounds.setOutlineColor(sf::Color::Red);
            _window.draw(bounds);    
            
            std::cout << component->getPosition().x << " " << component->getPosition().y << "\n";
        )
    }
    

    _collisionSystem.update();

    _window.display();
}