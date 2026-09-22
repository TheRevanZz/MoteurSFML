#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <unordered_map>

#include "Core/Component/BaseComponent.h"

class MultipleSpriteComponent : public se3::BaseComponent
{

protected:
    sf::Sprite* _pSprite;
    std::unordered_map<int, std::shared_ptr<sf::Texture>> _textures = {};
    uint8_t _textureIndex = 0u;

public:
    
    MultipleSpriteComponent(IGameComponent* owner, std::vector<const char*> texturesPaths, sf::Sprite* pSprite,
                            uint8_t textureIndex);
    MultipleSpriteComponent(IGameComponent* owner, std::vector<std::string> texturesPaths, sf::Sprite* pSprite,
                            uint8_t textureIndex);
    
    void ChangeTexture(uint8_t index);
    const std::unordered_map<int, std::shared_ptr<sf::Texture>>& GetTextures() const;
    

private:
    void Init(const std::vector<std::string>& texturesPaths);
};
