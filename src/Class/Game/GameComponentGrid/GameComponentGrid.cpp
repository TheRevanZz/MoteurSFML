#include "GameComponentGrid.h"

#include <ranges>
#include <utility>
#include <IGameComponent/IGameComponent.h>

#include "Game/WindowData/WindowData.h"


GameComponentGrid::GameComponentGrid(const int cellSize)
    : _grids(GridT(GRID_INIT_SIZE, std::vector<EntitiesCell>(GRID_INIT_SIZE))), _cellSize(cellSize)
{
}

void GameComponentGrid::Update()
{
    Clear();
    assert(_components != nullptr && "LE COMPONENT NOT INITIALIZED");
    for (const auto& cell : *_components)
    {
        Insert(cell);
    }
}

void GameComponentGrid::SetComponents(std::vector<std::shared_ptr<IGameComponent>>* components)
{
    _components = components;
}

void GameComponentGrid::Clear()
{
    _outOfGridsComponents.clear();
    for (auto& column : _grids)
    {
        for (auto& cell : column)
        {
            cell.clear();
        }
    }
}

void GameComponentGrid::Insert(const std::shared_ptr<IGameComponent>& component)
{
    auto [x,y] = GetCellPosition(component);
    if (const auto bounds = component->GetBounds();
        static_cast<float>(x) < -bounds.size.x ||
        static_cast<float>(y) < -bounds.size.y ||
        std::cmp_greater(x, WindowData::GetScreenSize().x) ||
        std::cmp_greater(y, WindowData::GetScreenSize().y)
    )
    {
        this->_outOfGridsComponents.push_back(component);
        return;
    }
    this->_grids[x][y].push_back(component);
}

std::vector<std::shared_ptr<IGameComponent>> GameComponentGrid::GetNearComponents(
    const std::shared_ptr<IGameComponent>& gameComponent) const
{
    auto [x,y] = GetCellPosition(gameComponent);

    auto entities = this->_grids[x][y];

    for (int dx = -1; dx <= 1; ++dx)
    {
        const int nx = x + dx;

        if (nx < 0 || std::cmp_greater_equal(nx, _grids.size()))
            continue;

        for (int dy = -1; dy <= 1; ++dy)
        {
            const int ny = y + dy;

            if (ny < 0 || std::cmp_greater_equal(ny, _grids[nx].size()))
                continue;

            entities.insert(
                entities.end(),
                _grids[nx][ny].begin(),
                _grids[nx][ny].end()
            );
        }
    }

    auto filteredEntities = entities | std::views::filter([gameComponent](const auto& _gameComponent)
    {
        return _gameComponent != gameComponent;
    });

    return {filteredEntities.begin(), filteredEntities.end()};
}

std::pair<int, int> GameComponentGrid::GetCellPosition(const std::shared_ptr<IGameComponent>& component)
{
    const int x = static_cast<int>(component->GetPosition().x / CELL_SIZE);
    const int y = static_cast<int>(component->GetPosition().y / CELL_SIZE);
    return {x, y};
}

std::vector<std::shared_ptr<IGameComponent>>* GameComponentGrid::GetComponents() const
{
    return _components;
}

std::vector<std::shared_ptr<IGameComponent>>* GameComponentGrid::GetComponents()
{
    return _components;
}

const std::vector<std::shared_ptr<IGameComponent>>& GameComponentGrid::GetOutOfGridsComponents() const
{
    return _outOfGridsComponents;
}
