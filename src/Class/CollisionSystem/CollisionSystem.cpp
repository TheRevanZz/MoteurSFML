//
// Created by sylvi on 16/09/2026.
//

#include "CollisionSystem.h"

#include <ranges>
#include <iostream> 
#include <list>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Debug.h"

CollisionSystem::CollisionSystem()
    : _grids(GridT(GRID_INIT_SIZE, std::vector<EntitiesCell>(GRID_INIT_SIZE)))
{}

/**
 * 
 * @param gameComponent Le gameComponent pour lequel on cherche les components voisins
 * @return L'ensemble des entités proche du gameComponent
 */
std::vector<std::shared_ptr<IGameComponent>> CollisionSystem::getNearComponents(
    const std::shared_ptr<IGameComponent>& gameComponent)
{
    auto [x,y] = getCell(gameComponent);
    
    auto entities = this->_grids[x][y];
    
    for (int dx = -1; dx <= 1; ++dx)
    {
        const int nx = x + dx;

        if (nx < 0 || nx >= static_cast<int>(_grids.size()))
            continue;

        for (int dy = -1; dy <= 1; ++dy)
        {
            const int ny = y + dy;

            if (ny < 0 || ny >= static_cast<int>(_grids[nx].size()))
                continue;

            entities.insert(
                entities.end(),
                _grids[nx][ny].begin(),
                _grids[nx][ny].end()
            );
        }
    }
    
    auto filteredEntities=  entities | std::views::filter([gameComponent](const auto& _gameComponent)
    {
        return _gameComponent != gameComponent;
    });
    
    return {filteredEntities.begin(), filteredEntities.end()};
}

void CollisionSystem::update()
{
    clearGrid();
    
    for (const auto& component : _components)
    {
        insertInGrid(component);
    }
    
    for (const auto& component : _components)
    {
        DEBUG_ONLY(
            std::cout << "COMPONENT 1\n";
        )

        for (
            auto nearEntities = getNearComponents(component);
            const auto& entity : nearEntities
        )
        {
            if (const auto optional_value = entity->getBounds().findIntersection(component->getBounds()); 
                optional_value.has_value())
            {
                entity->Collision(component);
                component->Collision(entity);
            }
        }
        
    }
}

void CollisionSystem::addComponents(const std::vector<std::shared_ptr<IGameComponent>>& components)
{
    _components.insert(_components.end(), components.begin(), components.end());
}

void CollisionSystem::insertInGrid(const std::shared_ptr<IGameComponent>& component)
{
    auto [x,y] = getCell(component);
    this->_grids[x][y].push_back(component);
}

std::pair<int, int> CollisionSystem::getCell(const std::shared_ptr<IGameComponent>& component)
{
    const int x = static_cast<int>(std::abs(component->getPosition().x) / CELL_SIZE);
    const int y = static_cast<int>(std::abs(component->getPosition().y) / CELL_SIZE);
    return {x, y};
}

void CollisionSystem::clearGrid()
{
    for (auto& column : _grids)
    {
        for (auto& cell : column)
        {
            cell.clear();
        }
    }
}
