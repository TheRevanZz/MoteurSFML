//
// Created by sylvi on 15/09/2026.
//

#pragma once

#include "Character/BaseCharacter/BaseCharacter.h"

class Ennemy: public BaseCharacter {

public:
    Ennemy(const sf::Texture& texture, float life);
    
    void Destruct() override;
    
    const sf::Drawable& getDrawable() const override;
    const sf::Vector2f getPosition() const override;
    const sf::FloatRect getBounds() const override;
    const sf::Transform getTransform() const override { return _sprite.getTransform();}
    void takeDamage(const float& damage) override {}


    void update() override {}

};


