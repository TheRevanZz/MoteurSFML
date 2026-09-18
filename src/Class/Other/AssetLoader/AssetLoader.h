#pragma once
#include <memory>
#include <string>
#include <unordered_map>

namespace sf
{
    class Texture;
}

class AssetLoader
{
    
public:
    static AssetLoader* getInstance();
    
    std::string loadTexture(const char* _path);
    std::shared_ptr<sf::Texture> getTexture(const char* texturePath) const;

private:
    static AssetLoader* _pAssetLoader;
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> _textures;
	
    AssetLoader() = default;
    ~AssetLoader() = default;
};
