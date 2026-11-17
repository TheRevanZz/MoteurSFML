//
// Created by evant on 24/09/2026.
//

#include "GameScene.h"

#include "MainMenuScene.h"
#include "Core/GameplayData/GameplayData.h"
#include "Core/Scene/SceneManager.h"
#include "Other/AssetLoader/AssetLoader.h"

GameScene::GameScene()
{
    start();
    PreLoadTexture();
    if (!_asteroidTexture.loadFromFile("ressources/images/entity_textures/static_entity_textures/static_entity_0.png"))
        abort();
    GameplayData::SetComponents(&_components);
}

void GameScene::start()
{
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
    _ennemyFactory.SetComponentsList(&_components);
}

void GameScene::update(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
    {
        SceneManager::getInstance().setActiveScene("MainMenuScene");
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
    {
        _player->Shoot();
    }
}

void GameScene::Render(sf::RenderWindow& window)
{

}

void GameScene::PreLoadTexture()
{
    auto pAssetLoader = AssetLoader::GetInstance();
    pAssetLoader->LoadTexture("ressources/images/player_textures/spaceship_1.png");
    pAssetLoader->LoadTexture("ressources/images/player_textures/spaceship_2.png");
    pAssetLoader->LoadTexture("ressources/images/player_textures/spaceship_3.png");
    pAssetLoader->LoadTexture("ressources/images/player_textures/spaceship_4.png");
}
