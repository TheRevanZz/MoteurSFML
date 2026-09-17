#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <unordered_map>

class MultipleSpriteComponent
{
    
protected:
    sf::Sprite* _sprite;
    std::unordered_map<int, sf::Texture> _textures = {};
    uint8_t _spriteIndex = 0u;
    
public:
    MultipleSpriteComponent(std::vector<std::string> texturesPaths, sf::Sprite* pSprite);
    
    void changeTexture(uint8_t index);
};
