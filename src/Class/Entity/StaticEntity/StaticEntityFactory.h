//
// Created by evant on 17/09/2026.
//

#pragma once

#include <memory>
#include "IGameComponent/IGameComponent.h"
#include <vector>
#include <SFML/Graphics/Texture.hpp>

class StaticEntity;


using ComponentsList = std::vector<std::shared_ptr<IGameComponent>>;

class StaticEntityFactory
{
public:
    StaticEntityFactory() = default;
    // ~StaticEntityFactory() {if (_components) delete _components;};

    void setComponentsList(ComponentsList* components) {_components = components;};
   ComponentsList* getComponentsList() const { return _components; };

    std::shared_ptr<StaticEntity> createStaticEntity();
    void deleteStaticEntity(const StaticEntity* pEntity) const;

protected:
    ComponentsList* _components = nullptr;

    // à réfléchir
    sf::Texture _asteroidTexture;

    std::array<int,4> mm = {1,2,3,4 };


};
