#pragma once

namespace sf::Keyboard
{
    enum class Key;
}

class IControllable
{
public:
    virtual ~IControllable() = default;
    sf::Keyboard::Key Left;
    sf::Keyboard::Key Right;
    sf::Keyboard::Key Up;
    sf::Keyboard::Key Down;
    
    virtual void handleMovement() = 0;
};
