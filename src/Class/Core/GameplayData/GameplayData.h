#pragma once

#include <vector>
#include <memory>
#include <SFML/System/Clock.hpp>

#include "Core/GameObject/IGameComponent/IGameComponent.h"

namespace sf
{
    class Clock;
}

class IGameComponent;

class GameplayData
{
protected:
    
    static std::vector<IGameComponent*> _players;
    static std::vector<std::shared_ptr<IGameComponent>>* _components;
    static std::vector<std::shared_ptr<IGameComponent>>* _componentsToAdd;
    static sf::Clock* _clock;

public:
    static std::vector<std::shared_ptr<IGameComponent>>* GetComponents() { return _components; }
    static void SetComponents(std::vector<std::shared_ptr<IGameComponent>>* components) { _components = components; }
    
    static std::vector<std::shared_ptr<IGameComponent>>* GetComponentsToAdd() { return _componentsToAdd; }
    static void SetComponentsToAdd(std::vector<std::shared_ptr<IGameComponent>>* components) { _componentsToAdd = components; }
    
    static sf::Clock* GetClock() { return _clock; }
    static void InitGameClock() { _clock = new sf::Clock(); _clock->start(); }
    
    static void RegisterPlayer(IGameComponent* player) { _players.push_back(player); }
    static std::vector<IGameComponent*> GetPlayers() { return _players; }
    
    static void RemovePlayer(const int index)
    {
        if (_players.empty())
            return;
        _players[index % _players.size()]->SetMustDie();
    }
};

inline std::vector<std::shared_ptr<IGameComponent>>* GameplayData::_components = nullptr;
inline std::vector<std::shared_ptr<IGameComponent>>* GameplayData::_componentsToAdd = nullptr;
inline sf::Clock* GameplayData::_clock = nullptr;
inline std::vector<IGameComponent*> GameplayData::_players = {};