#include "MultipleSpriteComponent.h"
#include <ranges>
#include <unordered_set>

MultipleSpriteComponent::MultipleSpriteComponent(
    std::vector<std::string> texturesPaths, 
    sf::Sprite* pSprite)
    : _sprite(pSprite), _textures(texturesPaths.size() + 1)
{
    std::unordered_set<std::string> texturesAdded = {};
    int i = 0;
    for (const auto& path : texturesPaths){
        if (!texturesAdded.insert(path).second)
            continue;
        _textures[i] = sf::Texture(path);
        i++;
    }
}

void MultipleSpriteComponent::changeTexture(const uint8_t index)
{
    if (index >= _textures.size())
        return;
    _spriteIndex = index;
    _sprite->setTexture(_textures[index]);
}
