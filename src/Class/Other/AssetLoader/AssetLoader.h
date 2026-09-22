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
    static AssetLoader* GetInstance();
    
    std::string LoadTexture(const char* _path);
    
    static sf::Texture LoadAndGetTexture(const char* path);
    std::shared_ptr<sf::Texture> GetTexture(const char* texturePath) const;

private:
    static AssetLoader* _pAssetLoader;
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> _textures;
	
    AssetLoader() = default;
    ~AssetLoader() = default;
};
