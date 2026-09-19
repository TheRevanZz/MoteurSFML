#include "GameWindow.h"
#include <iostream>
#include <ranges>

#include "Character/Player/Player.h"
#include "Macro/Debug.h"
#include "Game/Time/Time.h"
#include "Game/WindowData/WindowData.h"
#include "Other/AssetLoader/AssetLoader.h"


GameWindow::GameWindow()
{
    PreLoadTexture();
    if (!_asteroidTexture.loadFromFile("ressources/images/entity_textures/static_entity_0.png"))
        abort();
}

void GameWindow::Show(const int width, const int height, const std::string& title)
{
    _window.create(sf::VideoMode(sf::Vector2u(width, height)), title);
    _window.setFramerateLimit(60);
    WindowData::SetWindow(&_window);

    this->_player = std::make_shared<Player>(std::vector({
        "ressources/images/player_textures/spaceship_1.png",
        "ressources/images/player_textures/spaceship_2.png",
        "ressources/images/player_textures/spaceship_3.png",
        "ressources/images/player_textures/spaceship_4.png",
    }));
    
    this->_player->SetPosition({-_player->GetScaledSize().x / 2.f, _player->GetScaledSize().y / 2.f});
    
    this->_player2 = std::make_shared<Player>(
        std::vector({
            "ressources/images/player_textures/spaceship_1.png",
            "ressources/images/player_textures/spaceship_2.png",
            "ressources/images/player_textures/spaceship_3.png",
            "ressources/images/player_textures/spaceship_4.png",
        }),2);
    this->_player2->SetPosition({-100, -100});
    // if (this->_player2->ChangeKey(EActionTag::UP, sf::Keyboard::Key::Num0))
    // {
    //
    // }

    _components = { _player, _player2 };

    _gameComponentGrid.SetComponents(&_components);

    _staticEntityFactory.SetComponentsList(&_components);
    
    _staticEntityFactory.CreateStaticEntity();
    
    _clock.start();
    
    while (_window.isOpen())
    {
        ProcessEvents();
        auto time = _clock.restart();
        _deleteComponentTimer += time.asSeconds();
        Time::update(time);
        _gameComponentGrid.Update();
        Render();
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

void GameWindow::Render()
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

    for (const auto& component : _components)
    {
        if (auto* UpdateableCompoent = dynamic_cast<IUpdateable*>(component.get()); UpdateableCompoent != nullptr)
        {
            UpdateableCompoent->update();
        }
        _window.draw(component->getDrawable());
        DEBUG_ONLY(
            // sf::RectangleShape bounds(sf::Vector2f(component->getBounds().size.x, component->getBounds().size.y));
            // bounds.setPosition(component->getPosition());
            // bounds.setFillColor(sf::Color::Transparent);
            // bounds.setOutlineThickness(4.f);
            // bounds.setOutlineColor(sf::Color::Red);
            // _window.draw(bounds);
            //
            // std::cout << component->getPosition().x << " " << component->getPosition().y << "\n";
        )
    }


    if (_deleteComponentTimer >= 10.f)
    {
        DeleteComponentsOutOfWindow();
        _deleteComponentTimer -= 10.f;
    }
    _collisionSystem.compute(_gameComponentGrid);

    _window.display();
}


void GameWindow::PreLoadTexture()
{
    auto pAssetLoader = AssetLoader::getInstance();
    pAssetLoader->loadTexture("ressources/images/player_textures/spaceship_1.png");
    pAssetLoader->loadTexture("ressources/images/player_textures/spaceship_2.png");
    pAssetLoader->loadTexture("ressources/images/player_textures/spaceship_3.png");
    pAssetLoader->loadTexture("ressources/images/player_textures/spaceship_4.png");
}

void GameWindow::DeleteComponentsOutOfWindow()
{
    const auto& outOfWindowComponent = _gameComponentGrid.GetOutOfGridsComponents();
    
    // std::cout << "NB OUT OF GRID : " << outOfWindowComponent.size();
    if (outOfWindowComponent.empty())
        return;
    
    for (auto it = _components.begin(); it != _components.end();)
    {
        //Si la view n'est pas empty, ça veut dire qu'une correspondance a été trouvé dans outOfWindowComponent par rapport à it.
        auto IsPresent = outOfWindowComponent | std::ranges::views::filter([it](const std::shared_ptr<IGameComponent>& component)
        {
           return component == *it;
        });
        
        if (IsPresent.empty())
        {
            ++it;
        }
        else
        {
            it = _components.erase(it);
        }
    }
    
}
