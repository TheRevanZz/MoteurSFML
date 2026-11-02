//
// Created by evant on 24/09/2026.
//

#pragma once
#include <map>

#include "Core/Scene/Scene.h"
#include "Scenes/GameScene.h"


class SceneManager
{
public:
    static SceneManager& getInstance()
    {
        static SceneManager instance;
        return instance;
    }

    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    void setActiveScene(std::string nom);
    void update(float dt);
    void render(sf::RenderWindow& window);

    void addScene(std::unique_ptr<Scene> newScene, std::string sceneName);
    void removeScene(std::string sceneName);
    std::vector<std::string> getSceneNames() const;
    void setActiveScene(const std::unique_ptr<GameScene>& nom);

protected:
    SceneManager();

    // std::vector<std::shared_ptr<Scene>> _sceneList;
    std::map<std::string, std::unique_ptr<Scene>> _sceneList;

    std::unique_ptr<Scene> _activeScene;
    std::string _sceneName;

};
