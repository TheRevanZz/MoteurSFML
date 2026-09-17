//
// Created by evant on 17/09/2026.
//

#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "IGameComponent/IGameComponent.h"

class BaseEntity :
    public IGameComponent
{
public:
    BaseEntity(const sf::Texture& texture);

protected:
    sf::Sprite _sprite;
};
