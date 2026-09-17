#include "AssetLoader.h"

#include <cassert>
#include <SFML/Graphics/Texture.hpp>

AssetLoader* AssetLoader::pAssetLoader = nullptr;

AssetLoader* AssetLoader::getInstance()
{
    if(pAssetLoader == nullptr)
    {
        pAssetLoader = new AssetLoader();
    }
    return pAssetLoader;
}

void AssetLoader::loadImage(std::string _path)
{
    auto pTexture = new sf::Texture();
    bool succeeded = pTexture->loadFromFile(_path);
    assert(succeeded && "failed to load file");
    images[_path] = pTexture;
}

sf::Texture* AssetLoader::getImage(std::string _name)
{
    return images[_name];
}

