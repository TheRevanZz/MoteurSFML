//
// Created by evant on 17/09/2026.
//

#pragma once

#include <memory>

#include "StaticEntity.h"

using ComponentsList = std::vector<std::shared_ptr<IGameComponent>>;

class StaticEntityFactory
{
public:
    StaticEntityFactory();
    ~StaticEntityFactory() {if (_components) delete _components;};

    void setComponentsList(ComponentsList* components) {_components = components;};
   ComponentsList* getComponentsList() const { return _components; };

    std::shared_ptr<StaticEntity> createStaticEntity();
    // void deleteStaticEntity(std::shared_ptr<StaticEntity> entity);

protected:
    ComponentsList* _components;

    // à réfléchir
    sf::Texture _asteroidTexture;


};