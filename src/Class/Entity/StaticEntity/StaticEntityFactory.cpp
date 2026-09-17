//
// Created by evant on 17/09/2026.
//

#include "StaticEntityFactory.h"

StaticEntityFactory::StaticEntityFactory()
{
}

std::shared_ptr<StaticEntity> StaticEntityFactory::createStaticEntity()
{
    DirectBonus bonus{1.f, EBonusCategory::SPEED, true};

    if (!_asteroidTexture.loadFromFile("ressources/images/entity_textures/static_entity_0.png"))
    {
        abort();
    }
    _asteroidTexture.setSmooth(true);

    std::shared_ptr<StaticEntity> entity = std::make_shared<StaticEntity>(_asteroidTexture, std::make_shared<DirectBonus>(bonus));

    _components->push_back(entity);


    return entity;
}
