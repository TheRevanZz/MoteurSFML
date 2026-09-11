#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GameWindow.h"
 
int main()
{
    // Create the main window
    GameWindow window_test;
    window_test.show(800, 600, "Messi le GOAT");
 
    // // Create a graphical text to display
    // const sf::Font font("ressources/arial.ttf");
    // sf::Text text(font, "Hello SFML", 50);
    
    return 0;
}
