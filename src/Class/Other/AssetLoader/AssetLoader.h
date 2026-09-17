#pragma once
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

    void loadImage(std::string _path);
    sf::Texture* getImage(std::string _name);

private:
    static AssetLoader* pAssetLoader;

    std::unordered_map<std::string, sf::Texture*> images;
	
    AssetLoader() = default;
    ~AssetLoader() = default;
};
