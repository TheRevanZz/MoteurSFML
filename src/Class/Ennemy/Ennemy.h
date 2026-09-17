//
// Created by sylvi on 15/09/2026.
//

#pragma once

#include "BaseCharacter/BaseCharacter.h"
#include "GameWindow/GameWindow.h"


class Ennemy: public BaseCharacter {

public:
    Ennemy(const sf::Texture& texture, const ScreenPoint& screenSize, int life);
};


