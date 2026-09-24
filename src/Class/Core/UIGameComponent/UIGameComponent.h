#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

namespace  se3
{
    class UIGameComponent
    {
    public:
        virtual ~UIGameComponent() = default;
        virtual void Draw(sf::RenderWindow& window) = 0;
        virtual void Update() = 0;
        
        virtual float GetWidth() const = 0;
        virtual float GetHeight() const = 0;
    };
    
}
