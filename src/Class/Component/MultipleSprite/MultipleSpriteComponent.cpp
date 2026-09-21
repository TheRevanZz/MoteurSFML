#include "MultipleSpriteComponent.h"

#include <ranges>
#include <unordered_set>

#include "Class/Core/GameObject/IGameComponent/IGameComponent.h"
#include "Other/AssetLoader/AssetLoader.h"

void MultipleSpriteComponent::Init(const std::vector<std::string>& texturesPaths)
{
    const auto pAssetLoader = AssetLoader::GetInstance();
    std::unordered_set<std::string> texturesAdded = {};
    int i = 0;

    for (const auto& path : texturesPaths)
    {
        pAssetLoader->LoadTexture(path.c_str());
        if (!texturesAdded.insert(path).second)
            continue;
        const auto p = pAssetLoader->GetTexture(path.c_str());
        if (p == nullptr)
            continue;
        _textures[i] = p;
        i++;
    }
}


MultipleSpriteComponent::MultipleSpriteComponent(
    IGameComponent* owner,
    std::vector<const char*> texturesPaths,
    sf::Sprite* pSprite, const uint8_t textureIndex)
    : BaseComponent(owner), _pSprite(pSprite), _textures(texturesPaths.size() + 1), _textureIndex(textureIndex)
{
    const std::vector<std::string> vec(texturesPaths.begin(), texturesPaths.end());
    Init(vec);
}

MultipleSpriteComponent::MultipleSpriteComponent(
    IGameComponent* owner,
    std::vector<std::string> texturesPaths,
    sf::Sprite* pSprite, const uint8_t textureIndex
)
    : BaseComponent(owner), _pSprite(pSprite), _textures(texturesPaths.size() + 1), _textureIndex(textureIndex)
{
    Init(texturesPaths);
}

void MultipleSpriteComponent::ChangeTexture(const uint8_t index)
{
    if (index >= _textures.size())
        return;
    _textureIndex = index;
    _pSprite->setTexture(*_textures[index]);
}

const std::unordered_map<int, std::shared_ptr<sf::Texture>>& MultipleSpriteComponent::GetTextures() const
{
    return _textures;
}


