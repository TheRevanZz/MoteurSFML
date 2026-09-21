//
// Created by evant on 17/09/2026.
//

#include "StaticEntityFactory.h"

#include <iostream>

#include "Debug.h"
#include "Enum/EBonusCategory.h"
#include "StaticEntity.h"
#include "Game/Bonus/DirectBonus/DirectBonus.h"
#include "Game/Time/Time.h"
#include "GameWindow/GameWindow.h"


StaticEntityFactory::StaticEntityFactory()
{
    _clock.restart();
    _generationTimer = sf::seconds(5);
    DEBUG_ONLY(
        std::cout << "Generation d'un static entity dans " << _generationTimer.asSeconds() << "s\n";
    )
}

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
    DirectBonus bonus{-300, EBonusCategory::SPEED, true,3};

    if (!_asteroidTexture.loadFromFile("ressources/images/entity_textures/static_entity_0.png"))
    {
        abort();
    }
    _asteroidTexture.setSmooth(true);

    auto entity = std::make_shared<StaticEntity>(_asteroidTexture, std::make_shared<DirectBonus>(std::move(bonus)), this);

    _pComponents->push_back(std::move(entity));
    DEBUG_ONLY(
        std::cout << _pComponents->size() << std::endl;
    )

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

void StaticEntityFactory::update()
{
    if (_clock.getElapsedTime() >= _generationTimer)
    {
        CreateStaticEntity();
        _generationTimer = sf::seconds(Time::randf(5, 30));
        DEBUG_ONLY(
            std::cout << "teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest\n";
            std::cout << "teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest\n";
            std::cout << "teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest\n";
            std::cout << "teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest\n";
            std::cout << "teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest\n";
            std::cout << "teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest\n";
            std::cout << "teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest\n";
            std::cout << "teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest\n";
            std::cout << "teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest\n";
            std::cout << "teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest\n";
            std::cout << "Generation d'un static entity : " << "\n";
            std::cout << "Prochaine generation dans " << _generationTimer.asSeconds() << "s\n";
        )
        _clock.restart();
    }
}
