//
// Created by sylvi on 15/09/2026.
//

#include "BaseCharacter.h"

#include "Other/AssetLoader/AssetLoader.h"

BaseCharacter::BaseCharacter(sf::Texture texture, const float life) 
    : _mainTexture(std::move(texture)), _sprite(_mainTexture)
{
    _life = life;
    _maxLife = life;
}

BaseCharacter::BaseCharacter(const char* texture_path, const float life)
    : _mainTexture(AssetLoader::LoadAndGetTexture(texture_path)), _sprite(_mainTexture)
{
    _life = life;
    _maxLife = life;
}

sf::Transformable& BaseCharacter::GetTransformable()
{
    return _sprite;
}

const sf::Transformable& BaseCharacter::GetTransformable() const
{
    return _sprite;
}

const sf::FloatRect BaseCharacter::GetBounds() const
{
    return _sprite.getGlobalBounds();
}

const sf::Drawable& BaseCharacter::GetDrawable() const
{
    return _sprite;
}
