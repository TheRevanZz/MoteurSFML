//
// Created by sylvi on 15/09/2026.
//

#include "Ennemy.h"

#include "Game/WindowData/WindowData.h"
#include "Other/Math/CMath.h"

Ennemy::Ennemy(const sf::Texture &texture, const float life)
    : BaseCharacter(texture, life)
{
    _sprite.setScale({.15f, .15f});

    float xpos = CMath::randf(-(static_cast<int>(WindowData::GetScreenSize().x / 2)), static_cast<int>(WindowData::GetScreenSize().x / 2 - _sprite.getGlobalBounds().size.x));
    float ypos = CMath::randf(-(static_cast<int>(WindowData::GetScreenSize().y / 2 - _sprite.getGlobalBounds().size.y)), static_cast<int>(WindowData::GetScreenSize().y / 2));

    _id = _count;

    // _sprite.setOrigin({_sprite.getGlobalBounds().size.x / 2.f, _sprite.getGlobalBounds().size.y / 2.f});

    // SetPosition({static_cast<float>(std::rand()%WindowData::GetScreenSize().x), static_cast<float>(std::rand()%WindowData::GetScreenSize().y)});
    SetPosition({xpos, ypos});
    _count++;
}

sf::Vector2f Ennemy::GetScaledSize() const
{
    const auto& scale = this->_sprite.getScale();
    const auto& size = this->_sprite.getLocalBounds().size;

    return {scale.x * size.x, scale.y * size.y};
}

void Ennemy::TakeDamage(const float& damage)
{
    _life -= damage;

    if (IsDead())
        Destruct();
}

void Ennemy::Collision(const std::shared_ptr<IGameComponent>& otherComponent)
{
    BaseCharacter::Collision(otherComponent);
}

void Ennemy::Destruct()
{
    SetMustDie();
}
