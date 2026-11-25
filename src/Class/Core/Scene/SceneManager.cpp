//
// Created by evant on 24/09/2026.
//

#include "SceneManager.h"

#include <iostream>

#include "Debug.h"
#include "Scenes/MainMenuScene.h"

void SceneManager::setActiveScene(std::string nom)
{
    if (_activeScene && !_sceneName.empty())
        _sceneList.at(_sceneName) = std::move(_activeScene);
    _sceneName = std::move(nom);
    _activeScene = std::move(_sceneList.at(_sceneName));
    DEBUG_ONLY(
        std::cout << "SceneManager::setActiveScene: " << _sceneName << std::endl;
        )
}

void SceneManager::update(float dt)
{
    if (_activeScene)
        _activeScene->update(dt);
}

void SceneManager::render(sf::RenderWindow& window)
{
    if (_activeScene)
        _activeScene->Render(window);
}

void SceneManager::addScene(std::unique_ptr<Scene> newScene, std::string newSceneName)
{
    _sceneList.insert({newSceneName, std::move(newScene)});
}

std::vector<std::string> SceneManager::getSceneNames() const
{
    std::vector<std::string> sceneNames;

    for (auto it = _sceneList.begin(); it != _sceneList.end(); ++it)
    {
        sceneNames.push_back((*it).first);
    }

    return sceneNames;
}

SceneManager::SceneManager()
{
    addScene(std::make_unique<MainMenuScene>(), "MainMenuScene");
    addScene(std::make_unique<GameScene>(), "GameScene");
    setActiveScene("MainMenuScene");
}
