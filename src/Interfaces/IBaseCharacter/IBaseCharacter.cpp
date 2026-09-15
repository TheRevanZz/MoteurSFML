//
// Created by sylvi on 15/09/2026.
//

#include "IBaseCharacter.h"

IBaseCharacter::IBaseCharacter(const sf::Texture& texture, int life) : _sprite(texture) {
    _life = life;
    _maxLife = life;
}
