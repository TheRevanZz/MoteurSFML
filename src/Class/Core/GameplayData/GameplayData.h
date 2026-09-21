#pragma once

#include <vector>
#include <memory>

class IGameComponent;

class GameplayData
{
protected:
    static std::vector<std::shared_ptr<IGameComponent>>* _components;

public:
    static std::vector<std::shared_ptr<IGameComponent>>* GetComponents() { return _components; }
    static void SetComponents(std::vector<std::shared_ptr<IGameComponent>>* components) { _components = components; }
};

inline std::vector<std::shared_ptr<IGameComponent>>* GameplayData::_components = nullptr;
