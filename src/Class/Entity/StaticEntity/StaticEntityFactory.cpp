//
// Created by evant on 17/09/2026.
//

#include "StaticEntityFactory.h"

#include <iostream>
#include "Enum/EBonusCategory.h"
#include "StaticEntity.h"
#include "Game/Bonus/DirectBonus/DirectBonus.h"

void StaticEntityFactory::SetComponentsList(ComponentsList* components)
{
    _pComponents = components;
}

ComponentsList* StaticEntityFactory::GetComponentsList() const
{
    return _pComponents;
}

std::shared_ptr<StaticEntity> StaticEntityFactory::CreateStaticEntity()
{
    DirectBonus bonus{1.f, EBonusCategory::SPEED, true};

    if (!_asteroidTexture.loadFromFile("ressources/images/entity_textures/static_entity_0.png"))
    {
        abort();
    }
    _asteroidTexture.setSmooth(true);

    auto entity = std::make_shared<StaticEntity>(_asteroidTexture, std::make_shared<DirectBonus>(std::move(bonus)), this);

    _pComponents->push_back(std::move(entity));

    return entity;
}

void StaticEntityFactory::DeleteStaticEntity(const StaticEntity* pEntity) const
{
    for (auto it = _pComponents->cbegin(); it != _pComponents->cend();)
    {
        if (std::dynamic_pointer_cast<StaticEntity>(*it).get() == pEntity)
        {
            it = _pComponents->erase(it);
        }
        else
            ++it;
    }
}
