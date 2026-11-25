#include "GameWindow.h"
#include <iostream>
#include <ranges>

#include "Character/Player/Player.h"
#include "Core/GameplayData/GameplayData.h"
#include "Macro/Debug.h"
#include "Game/Time/Time.h"
#include "Game/WindowData/WindowData.h"
#include "Other/AssetLoader/AssetLoader.h"


GameWindow::GameWindow()
{
    PreLoadTexture();
    if (!_asteroidTexture.loadFromFile("ressources/images/entity_textures/static_entity_textures/static_entity_0.png"))
        abort();
    GameplayData::SetComponents(&_components);
    GameplayData::SetComponentsToAdd(&_componentsToAdd);
}

void GameWindow::Show(const int width, const int height, const std::string& title)
{
    _window.create(sf::VideoMode(sf::Vector2u(width, height)), title);
    _window.setFramerateLimit(60);
    
    WindowData::SetWindow(&_window);
    GameplayData::InitGameClock();
    
    _components = {Player::MakePlayer()};

    _gameComponentGrid.SetComponents(&_components);

    _staticEntityFactory.SetComponentsList(&_components);
    _ennemyFactory.SetComponentsList(&_components);

    _clock.start();

    while (_window.isOpen())
    {
        ProcessEvents();
        Update();
        Render();
        _gameComponentGrid.Update();
        AddNewComponents();
    }
}

void GameWindow::ProcessEvents()
{
    while (const std::optional event = _window.pollEvent())
    {
        if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            _window.close();
        if (event->is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
        {
            auto p = Player::MakePlayer();
            if (p != nullptr)
                _components.push_back(std::move(p));
        }
        if (event->is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
        {
            GameplayData::RemovePlayer(0);
        }
        if (event->is<sf::Event::MouseButtonPressed>() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            std::cout << "CLKICKK\n";
            int index = 0;
            for (const auto& p : GameplayData::GetPlayers())
            {
                DEBUG_ONLY(
                    std::cout << "ok";    
                )
                if (CollisionSystem::IsColliding(
                    static_cast<sf::FloatRect>(*p),
                    sf::FloatRect(
                        static_cast<sf::Vector2f>(sf::Mouse::getPosition(_window)),
                        sf::Vector2f(10.f, 10.f)
                    )))
                {
                    GameplayData::RemovePlayer(index);
                    break;
                }
                index++;
            }
        }
    }
}

void GameWindow::Render()
{
    _window.clear();

    DEBUG_ONLY(
        sf::RectangleShape x_line({ 10000.f, 2.f});
        x_line.setFillColor(sf::Color::Red);

        x_line.setPosition(sf::Vector2f(CoordinateSystem::ToScreenPoint({0,0})));
        sf::RectangleShape y_line({ 10000.f, 2.f});
        y_line.setPosition(sf::Vector2f(CoordinateSystem::ToScreenPoint({0,0})));
        y_line.rotate(sf::degrees(-90));
        y_line.setFillColor(sf::Color::Red);

        _window.draw(x_line);
        _window.draw(y_line);
    )

    for (auto it = _components.begin(); it != _components.end();)
    {
        const auto& component = *it;
        if (component == nullptr || component->GetMustDie())
        {
            it = _components.erase(it);
            continue;
        }
        component->Draw(_window);
        DEBUG_ONLY(
            sf::RectangleShape bounds(sf::Vector2f(component->GetBounds().size.x, component->GetBounds().size.y));
            bounds.setPosition(component->GetPosition());
            bounds.setFillColor(sf::Color::Transparent);
            bounds.setOutlineThickness(4.f);
            bounds.setOutlineColor(sf::Color::Red);
            _window.draw(bounds);
        )
        ++it;
    }

    _window.display();
}

void GameWindow::Update()
{
    UpdateTime();

    for (auto it = _components.begin(); it != _components.end();)
    {
        const auto& component = *it;
        if (component == nullptr || component->GetMustDie())
        {
            it = _components.erase(it);
            continue;
        }
        if (auto* updateableComponent = dynamic_cast<IUpdateable*>(component.get()); updateableComponent != nullptr)
        {
            updateableComponent->update();
        }
        ++it;
    }

    if (_deleteComponentTimer >= 2.f)
    {
        DeleteComponentsOutOfWindow();
        _deleteComponentTimer -= 2.f;
    }

    _staticEntityFactory.update();
    _ennemyFactory.update();
    _collisionSystem.compute(_gameComponentGrid);
}


void GameWindow::PreLoadTexture()
{
    const auto pAssetLoader = AssetLoader::GetInstance();
    pAssetLoader->LoadTexture("ressources/images/player_textures/spaceship_1.png");
    pAssetLoader->LoadTexture("ressources/images/player_textures/spaceship_2.png");
    pAssetLoader->LoadTexture("ressources/images/player_textures/spaceship_3.png");
    pAssetLoader->LoadTexture("ressources/images/player_textures/spaceship_4.png");
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
        auto isPresent = outOfWindowComponent | std::ranges::views::filter(
            [it](const std::shared_ptr<IGameComponent>& component)
            {
                return component == *it;
            });

        if (isPresent.empty())
        {
            ++it;
        }
        else
        {
            it = _components.erase(it);
        }
    }
}

void GameWindow::AddNewComponents()
{
    _components.insert(
        _components.end(),
        std::make_move_iterator(_componentsToAdd.begin()),
        std::make_move_iterator(_componentsToAdd.end())
    );

    _componentsToAdd.clear();
}

void GameWindow::UpdateTime()
{
    const auto time = _clock.restart();
    _deleteComponentTimer += time.asSeconds();
    Time::update(time);
    std::cout << 1 / time.asSeconds() << "\n";
}
