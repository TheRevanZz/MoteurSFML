//
// Created by sylvi on 15/09/2026.
//
#pragma once
#include "IDamageable/IDamageable.h"
#include "IDestructable/IDestructable.h"
#include "IGameComponent/IGameComponent.h"
#include "IUpdateable/IUpdateable.h"
#include <SFML/Graphics.hpp>


class BaseBonus;

namespace sf {
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

