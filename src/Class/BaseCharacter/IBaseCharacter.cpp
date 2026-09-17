//
// Created by sylvi on 15/09/2026.
//

#include "BaseCharacter.h"

BaseCharacter::BaseCharacter(const sf::Texture& texture, const int life) : _sprite(texture) {
    _life = life;
    _maxLife = life;
}
