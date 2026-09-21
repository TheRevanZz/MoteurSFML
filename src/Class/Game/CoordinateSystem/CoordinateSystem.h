#pragma once
#include <SFML/System/Vector2.hpp>

namespace CoordinateSystem
{
    using WorldPoint = sf::Vector2f;
    using ScreenPoint = sf::Vector2i;
    
    ScreenPoint ToScreenPoint(const WorldPoint& worldPoint);

    WorldPoint ToWorldPoint(const ScreenPoint& screenPoint);
}
