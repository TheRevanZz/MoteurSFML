#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class WindowData
{
    
    static const sf::RenderWindow* _window;
    
public:
    
    ~WindowData(){ if (_window) delete _window; }
    
    [[nodiscard("La taille de l'écran a été retourner, ne pas ignorer")]]
    static sf::Vector2u GetScreenSize() { return _window->getSize(); }
    static void SetWindow(const sf::RenderWindow* const window) { _window = window; }
};

inline const sf::RenderWindow* WindowData::_window = nullptr;
