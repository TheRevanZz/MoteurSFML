//
// Created by sylvi on 15/09/2026.
//

#include "BaseCharacter.h"

BaseCharacter::BaseCharacter(const sf::Texture& texture, const float life) 
    : IGameComponent(texture) 
{
    _life = life;
    _maxLife = life;
}

BaseCharacter::BaseCharacter(const char* texture_path, float life)
    : IGameComponent(texture_path)
{
    _life = life;
    _maxLife = life;
}
