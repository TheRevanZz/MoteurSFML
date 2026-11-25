//
// Created by evant on 24/09/2026.
//

#include "MainMenuScene.h"

#include <iostream>

#include "Debug.h"
#include "GameScene.h"
#include "../Core/Scene/SceneManager.h"
#include "Other/AssetLoader/AssetLoader.h"

MainMenuScene::MainMenuScene()
    : _backgroundTexture(AssetLoader::LoadAndGetTexture("ressources/images/background.png"))
    , _backgroundSprite(_backgroundTexture)
{
    _backgroundSprite.setPosition({0, 0});
}

void MainMenuScene::start()
{

}

void MainMenuScene::update(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
    {
        SceneManager::getInstance().setActiveScene("GameScene");
        DEBUG_ONLY(
            std::cout << "Scene set\n";
        )
    }
    // std::cout << "update" << std::endl;
}

void MainMenuScene::Render(sf::RenderWindow& window)
{
    window.draw(_backgroundSprite);

    // std::cout << "Render" << std::endl;
}
