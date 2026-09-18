#include "AssetLoader.h"

#include <cassert>
#include <SFML/Graphics/Texture.hpp>


AssetLoader* AssetLoader::_pAssetLoader = nullptr;

AssetLoader* AssetLoader::getInstance()
{
    if(_pAssetLoader == nullptr)
    {
        _pAssetLoader = new AssetLoader();
    }
    return _pAssetLoader;
}


std::string AssetLoader::loadTexture(const char* _path)
{
    if (_textures.contains(_path))
        return _path;
    const auto pTexture = std::make_shared<sf::Texture>();
    const bool succeeded = pTexture->loadFromFile(_path);
    assert(succeeded && "failed to load file");
    if (!succeeded)
        return _path;
    _textures[_path] = pTexture;
    return _path;
}

std::shared_ptr<sf::Texture> AssetLoader::getTexture(const char* texturePath) const
{
    if (!_textures.contains(texturePath))
        return nullptr;
    return _textures.at(texturePath);
}

