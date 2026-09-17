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
    public IDamageable,
    public IDestructable
{

public:
    BaseCharacter(const sf::Texture& texture, int life);


protected:
    sf::Sprite _sprite;



};

