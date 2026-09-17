#pragma once

namespace sf
{
    class RenderWindow;
}

class IUpdateable
{
public:
    virtual ~IUpdateable() = default;
    virtual void update() = 0;
};
