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
#include "Other/Math/CMath.h"


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
    DirectBonus bonus{100, EBonusCategory::SPEED, true, 3};
    // DamageBonus damage{10, true, 3};

    if (!_asteroidTexture.loadFromFile("ressources/images/entity_textures/static_entity_textures/static_entity_0.png"))
    {
        abort();
    }
    _asteroidTexture.setSmooth(true);


    auto entity = std::make_shared<StaticEntity>(_asteroidTexture, std::make_shared<DirectBonus>(std::move(bonus)));
    _pComponents->push_back(std::move(entity));
    DEBUG_ONLY(
        std::cout << _pComponents->size() << "\n";
    )

    return nullptr;
}

void StaticEntityFactory::update()
{
    if (_clock.getElapsedTime() >= _generationTimer)
    {
        CreateStaticEntity();
        _generationTimer = sf::seconds(CMath::randf(5, 30));
        // _generationTimer = sf::seconds(5);
        DEBUG_ONLY(
        //     for (size_t i = 0; i < 100; ++i)
        //         std::cout << "teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest" << _generationTimer.asSeconds() << "\n";
        //     std::cout << -(static_cast<int>(WindowData::GetScreenSize().y / 2)) << std::endl;
            std::cout << "Generation d'un static entity : " << "\n";
            std::cout << "Prochaine generation dans " << _generationTimer.asSeconds() << "s\n";
        )
        _clock.restart();
    }
}
