//
// Created by evant on 24/09/2026.
//

#include "GameScene.h"

#include <iostream>
#include <ranges>

#include "Debug.h"
#include "MainMenuScene.h"
#include "Character/Player/Player.h"
#include "Core/GameplayData/GameplayData.h"
#include "Core/Scene/SceneManager.h"
#include "Other/AssetLoader/AssetLoader.h"

GameScene::GameScene()
    // : _backgroundTexture(AssetLoader::LoadAndGetTexture("ressources/images/maxresdefault.jpg"))
    // , _backgroundSprite(_backgroundTexture)
{
    // _backgroundSprite.setPosition({0, 0});
    start();
}

void GameScene::start()
{
    PreLoadTexture();
    if (!_asteroidTexture.loadFromFile("ressources/images/entity_textures/static_entity_textures/static_entity_0.png"))
        abort();
    GameplayData::SetComponents(&_components);

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

    _components = { _player, _player2 };

    _gameComponentGrid.SetComponents(&_components);

    _staticEntityFactory.SetComponentsList(&_components);
    _ennemyFactory.SetComponentsList(&_components);
}

void GameScene::update(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
    {
        SceneManager::getInstance().setActiveScene("MainMenuScene");
    }

    //!\\ test à modifier/enlever
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
    {
        _player->Shoot();
    }

    _deleteComponentTimer += dt;

    _staticEntityFactory.update();
    _ennemyFactory.update();

    std::cout << _components.size() << "\n";
    _collisionSystem.compute(_gameComponentGrid);

    if (_deleteComponentTimer >= 2.f)
    {
        DeleteComponentsOutOfWindow();
        _deleteComponentTimer -= 2.f;
    }
}

void GameScene::Render(sf::RenderWindow& window)
{
    // window.draw(_backgroundSprite);

    DEBUG_ONLY(
         sf::RectangleShape x_line({ 10000.f, 2.f});
         x_line.setFillColor(sf::Color::Red);

         x_line.setPosition(sf::Vector2f(CoordinateSystem::ToScreenPoint({0,0})));
         sf::RectangleShape y_line({ 10000.f, 2.f});
         y_line.setPosition(sf::Vector2f(CoordinateSystem::ToScreenPoint({0,0})));
         y_line.rotate(sf::degrees(-90));
         y_line.setFillColor(sf::Color::Red);

         window.draw(x_line);
         window.draw(y_line);
     )

    for (auto it = _components.begin(); it != _components.end();)
    {
        const auto& component = *it;
        if (component->GetMustDie()) {
            it = _components.erase(it);
            continue;
        }
        window.draw(component->getDrawable());

        if (auto* UpdateableCompoent = dynamic_cast<IUpdateable*>(component.get()); UpdateableCompoent != nullptr)
        {
            UpdateableCompoent->update();
        }
        DEBUG_ONLY(
            sf::RectangleShape bounds(sf::Vector2f(component->GetBounds().size.x, component->GetBounds().size.y));
            bounds.setPosition(component->GetPosition());
            bounds.setFillColor(sf::Color::Transparent);
            bounds.setOutlineThickness(4.f);
            bounds.setOutlineColor(sf::Color::Red);
            window.draw(bounds);

            // std::cout << component->getPosition().x << " " << component->getPosition().y << "\n";
        )
        ++it;
    }
}

void GameScene::PreLoadTexture()
{
    auto pAssetLoader = AssetLoader::GetInstance();
    pAssetLoader->LoadTexture("ressources/images/player_textures/spaceship_1.png");
    pAssetLoader->LoadTexture("ressources/images/player_textures/spaceship_2.png");
    pAssetLoader->LoadTexture("ressources/images/player_textures/spaceship_3.png");
    pAssetLoader->LoadTexture("ressources/images/player_textures/spaceship_4.png");
}

void GameScene::DeleteComponentsOutOfWindow()
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