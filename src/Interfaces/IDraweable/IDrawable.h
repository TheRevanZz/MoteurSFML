#pragma once

namespace sf
{
    class Drawable;
}

class IDrawable
{
public:
    virtual ~IDrawable() = default;
    [[nodiscard]] virtual const sf::Drawable* getDrawable() const = 0;
};
