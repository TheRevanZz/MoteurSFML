#pragma once

namespace sf
{
    class RenderWindow;
}

class IUpdateable
{
public:
    virtual ~IUpdateable() = default;
    virtual void update(sf::RenderWindow& window) = 0;
};
