//
// Created by evant on 24/09/2026.
//

#include "GameScene.h"

#include "MainMenuScene.h"
#include "Core/Scene/SceneManager.h"
#include "Other/AssetLoader/AssetLoader.h"

GameScene::GameScene()
    : _backgroundTexture(AssetLoader::LoadAndGetTexture("ressources/images/maxresdefault.jpg"))
    , _backgroundSprite(_backgroundTexture)
{
    _backgroundSprite.setPosition({0, 0});
    start();
}

void GameScene::start()
{
}

void GameScene::update(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
    {
        SceneManager::getInstance().setActiveScene("MainMenuScene");
    }
}

void GameScene::Render(sf::RenderWindow& window)
{
    window.draw(_backgroundSprite);
}
