#include "EnnemyFactory.h"

#include <iostream>

#include "Debug.h"
#include "Game/WindowData/WindowData.h"
#include "Other/Math/CMath.h"

EnnemyFactory::EnnemyFactory()
{
    _clock.restart();
    _generationTimer = sf::seconds(10);
    DEBUG_ONLY(
        std::cout << "Generation d'un ennemy dans " << _generationTimer.asSeconds() << "s\n";
    )
}

void EnnemyFactory::SetComponentsList(ComponentsList* components)
{
    _pComponents = components;
}

ComponentsList* EnnemyFactory::GetComponentsList() const
{
    return _pComponents;
}

void EnnemyFactory::CreateEnnemy()
{
    if (!_ennemyTexture.loadFromFile("ressources/images/entity_textures/ennemy_textures/ennemy_0.png"))
    {
        abort();
    }
    _ennemyTexture.setSmooth(true);


    auto ennemy = std::make_shared<Ennemy>(_ennemyTexture, CMath::randf(0, 200));
    _pComponents->push_back(std::move(ennemy));
    DEBUG_ONLY(
        std::cout << _pComponents->size() << std::endl;
    )
}

void EnnemyFactory::update()
{
    if (_clock.getElapsedTime() >= _generationTimer)
    {
        CreateEnnemy();
        _generationTimer = sf::seconds(CMath::randf(5, 30));
        // _generationTimer = sf::seconds(5);
        DEBUG_ONLY(
        //     for (size_t i = 0; i < 100; ++i)
        //         std::cout << "ennnnnnnnnnnnnnnnnnnnnnnnnnnnnemyyyyyyyyyyyyyyyy" << _generationTimer.asSeconds() << "\n";
        // std::cout << -(static_cast<int>(WindowData::GetScreenSize().y / 2)) << std::endl;
        std::cout << "Generation d'un ennemy : " << "\n";
        std::cout << "Prochaine generation dans " << _generationTimer.asSeconds() << "s\n";
        )
    _clock.restart();
    }
}
