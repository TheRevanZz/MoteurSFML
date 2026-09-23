//
// Created by sylvi on 15/09/2026.
//

#pragma once

#include "Character/BaseCharacter/BaseCharacter.h"

class Ennemy: public BaseCharacter {

public:
    Ennemy(const sf::Texture& texture, float life);
    
    void TakeDamage(const float& damage) override {}
    
    void update() override {}
};


