//
// Created by sylvi on 15/09/2026.
//

#pragma once

#include "GameWindow/GameWindow.h"
#include "IBaseCharacter/IBaseCharacter.h"


class Ennemy: public IBaseCharacter {

public:
    Ennemy(const sf::Texture& texture, const ScreenPoint& screenSize, int life);
};


