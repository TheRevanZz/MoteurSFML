#pragma once

#include <vector>
#include <memory>

constexpr int CELL_SIZE = 300;
constexpr int GRID_INIT_SIZE = 15;

class IGameComponent;

class GameComponentGrid
{
    using EntitiesCell = std::vector<std::shared_ptr<IGameComponent>>;
    using GridT = std::vector<std::vector<EntitiesCell>>;

public:
    explicit GameComponentGrid(int cellSize = CELL_SIZE);

    void update();
    void setComponents(std::vector<std::shared_ptr<IGameComponent>>* components);

    std::vector<std::shared_ptr<IGameComponent>>* getComponents() const;
    std::vector<std::shared_ptr<IGameComponent>>* getComponents();
    
    const std::vector<std::shared_ptr<IGameComponent>>& getOutOfGridsComponents() const;
    
    std::vector<std::shared_ptr<IGameComponent>> getNearComponents(
        const std::shared_ptr<IGameComponent>& gameComponent) const;
    
protected:
    GridT _grids;

    int _cellSize;

    std::vector<std::shared_ptr<IGameComponent>>* _components = nullptr;
    std::vector<std::shared_ptr<IGameComponent>> _outOfGridsComponents = {};

    void clear();
    void insert(const std::shared_ptr<IGameComponent>& component);
    static std::pair<int, int> getCellPosition(const std::shared_ptr<IGameComponent>& component);
};
