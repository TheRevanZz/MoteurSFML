//
// Created by sylvi on 15/09/2026.
//

#include "Ennemy.h"

Ennemy::Ennemy(const sf::Texture &texture, const float life)
    : BaseCharacter(texture, life)
{

}

void Ennemy::Destruct()
{
}

const sf::Drawable& Ennemy::getDrawable() const
{
    return _sprite;
}

const sf::Vector2f Ennemy::getPosition() const
{
    return _sprite.getPosition();
}

const sf::FloatRect Ennemy::getBounds() const
{
    return _sprite.getGlobalBounds();
}
