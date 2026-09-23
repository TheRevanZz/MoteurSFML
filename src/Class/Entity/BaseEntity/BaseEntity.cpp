//
// Created by evant on 17/09/2026.
//
#include "BaseEntity.h"

#include "Other/AssetLoader/AssetLoader.h"

BaseEntity::BaseEntity(const sf::Texture& texture)
    :_mainTexture(texture), _sprite(_mainTexture)
{
}

BaseEntity::BaseEntity(const char* texturePath)
    : _mainTexture(AssetLoader::LoadAndGetTexture(texturePath)), _sprite(_mainTexture)
{
}

const sf::Transformable& BaseEntity::GetTransformable() const
{
    return _sprite;
}

sf::Transformable& BaseEntity::GetTransformable()
{
    return _sprite;
}

const sf::Drawable& BaseEntity::getDrawable() const
{
    return _sprite;
}

const sf::FloatRect BaseEntity::GetBounds() const
{
    return _sprite.getGlobalBounds();
}



