#pragma once

#include <SFML/Graphics.hpp>

class Time
{
    protected:
        static float _deltaTime;
        static float _timeSpeed;
    
    public:
        static void update(const sf::Time& dtTime) { _deltaTime = dtTime.asSeconds(); }
        static float deltaTime() { return _deltaTime * _timeSpeed; }
        static void setTimeSpeed(const float& timeSpeed) { _timeSpeed = timeSpeed; }
        
};

inline float Time::_deltaTime = 0.0f;
inline float Time::_timeSpeed = 1.f;