#pragma once

namespace sf
{
    class Drawable;
}

class IDrawable
{
public:
    virtual ~IDrawable() = default;
    virtual const sf::Drawable* getDrawable() const = 0;
};
