//
// Created by sylvi on 16/09/2026.
//

#pragma once

#include <memory>
#include <vector>

#include "IGameComponent/IGameComponent.h"

constexpr int CELL_SIZE = 300;
constexpr int GRID_INIT_SIZE = 15;

class CollisionSystem {

using EntitiesCell = std::vector<std::shared_ptr<IGameComponent>>;
using GridT = std::vector<std::vector<EntitiesCell>>;
    
public:
    explicit CollisionSystem();

    void update();
    void setComponents(const std::vector<std::shared_ptr<IGameComponent>>& components) { _components = components; }
    void addComponents(const std::vector<std::shared_ptr<IGameComponent>>& components);


    void insertInGrid(const std::shared_ptr<IGameComponent>& component);
    [[nodiscard]] std::vector<std::shared_ptr<IGameComponent>> getNearComponents(const std::shared_ptr<IGameComponent>& gameComponent);
    static std::pair<int,int> getCell(const std::shared_ptr<IGameComponent>& component);
    void clearGrid();
    
private:
    std::vector<std::shared_ptr<IGameComponent>> _components = {};
    
    GridT _grids;
};
