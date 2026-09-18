//
// Created by evant on 17/09/2026.
//
#include "BaseEntity.h"

BaseEntity::BaseEntity(const sf::Texture& texture)
    : IGameComponent(texture)
{
}

BaseEntity::BaseEntity(const char* texturePath)
    : IGameComponent(texturePath)
{
}
