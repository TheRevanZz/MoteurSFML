//
// Created by sylvi on 16/09/2026.
//

#pragma once

#include <memory>
#include <ranges>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

#include "IGameComponent/IGameComponent.h"

using ComponentsList = std::vector<std::shared_ptr<IGameComponent>>;

constexpr int CELL_SIZE = 300;
constexpr int GRID_INIT_SIZE = 15;

class CollisionSystem {

using EntitiesCell = std::vector<std::shared_ptr<IGameComponent>>;
using GridT = std::vector<std::vector<EntitiesCell>>;
    
public:
    explicit CollisionSystem();

    void update();
    void setComponents(ComponentsList* components) {_components = components;};
    std::shared_ptr<std::vector<std::shared_ptr<IGameComponent>>> getComponents() { return std::make_shared<std::vector<std::shared_ptr<IGameComponent>>>(*_components); };
    
protected:

    ComponentsList* _components;
    GridT _grids;

    void insertInGrid(const std::shared_ptr<IGameComponent>& component);
    [[nodiscard]] std::vector<std::shared_ptr<IGameComponent>> getNearComponents(const std::shared_ptr<IGameComponent>& gameComponent);
    static std::pair<int,int> getCell(const std::shared_ptr<IGameComponent>& component);
    void clearGrid();
};
