//
// Created by evant on 17/09/2026.
//

#pragma once

#include <memory>
#include <vector>
#include <array>
#include <SFML/Graphics/Texture.hpp>

class StaticEntity;
class IGameComponent;

namespace sf
{
    class Texture;
}


using ComponentsList = std::vector<std::shared_ptr<IGameComponent>>;

class StaticEntityFactory
{
public:
    StaticEntityFactory() = default;
    // ~StaticEntityFactory() {if (_components) delete _components;};

    void SetComponentsList(ComponentsList* components);
    ComponentsList* GetComponentsList() const;

    std::shared_ptr<StaticEntity> CreateStaticEntity();
    void DeleteStaticEntity(const StaticEntity* pEntity) const;

protected:
    ComponentsList* _pComponents = nullptr;

    // à réfléchir
    sf::Texture _asteroidTexture;

    std::array<int,4> mm = {1,2,3,4 };
};
