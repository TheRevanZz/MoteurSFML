//
// Created by sylvi on 15/09/2026.
//
#pragma once
#include <SFML/Graphics.hpp>

#include "IDamageable/IDamageable.h"
#include "Class/Core/GameObject/IGameComponent/IGameComponent.h"
#include "IUpdateable/IUpdateable.h"

class BaseBonus;

namespace sf
{
    class Texture;
}

class BaseCharacter :
    public IGameComponent,
    public IUpdateable,
    public IDamageable
{
public:
    BaseCharacter(const sf::Texture& texture, float life);
    BaseCharacter(const char* texture_path, float life);
};
