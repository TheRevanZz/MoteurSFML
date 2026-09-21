#pragma once

#include <vector>
#include <memory>

constexpr int CELL_SIZE = 150;
constexpr int GRID_INIT_SIZE = 15;

class IGameComponent;

class GameComponentGrid
{
    using EntitiesCell = std::vector<std::shared_ptr<IGameComponent>>;
    using GridT = std::vector<std::vector<EntitiesCell>>;

public:
    explicit GameComponentGrid(int cellSize = CELL_SIZE);

    void Update();
    void SetComponents(std::vector<std::shared_ptr<IGameComponent>>* components);

    std::vector<std::shared_ptr<IGameComponent>>* GetComponents() const;
    std::vector<std::shared_ptr<IGameComponent>>* GetComponents();
    
    const std::vector<std::shared_ptr<IGameComponent>>& GetOutOfGridsComponents() const;
    
    std::vector<std::shared_ptr<IGameComponent>> GetNearComponents(
        const std::shared_ptr<IGameComponent>& gameComponent) const;
    
protected:
    GridT _grids;

    int _cellSize;

    std::vector<std::shared_ptr<IGameComponent>>* _components = nullptr;
    std::vector<std::shared_ptr<IGameComponent>> _outOfGridsComponents = {};

    void Clear();
    void Insert(const std::shared_ptr<IGameComponent>& component);
    static std::pair<int, int> GetCellPosition(const std::shared_ptr<IGameComponent>& component);
};
