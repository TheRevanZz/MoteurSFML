#pragma once

namespace sf
{
    class Drawable;
}

class IDrawable
{
public:
    virtual ~IDrawable() = default;
    virtual const sf::Drawable& GetDrawable() const = 0;
};
