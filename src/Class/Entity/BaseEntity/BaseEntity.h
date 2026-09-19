//
// Created by evant on 17/09/2026.
//

#pragma once
#include "IGameComponent/IGameComponent.h"

namespace sf
{
    class Texture;
}

class BaseEntity :
    public IGameComponent
{
public:
    explicit BaseEntity(const sf::Texture& texture);
    explicit BaseEntity(const char* texturePath);
};
