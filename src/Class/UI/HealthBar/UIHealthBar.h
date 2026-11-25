#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Core/UIGameComponent/UIGameComponent.h"
#include "ILife/ILife.h"

class ILife;

class UIHealthBar : public se3::UIGameComponent
{
    
    struct params
    {
        sf::Color background_color;
        sf::Color main_color;
        ILife* element;
        sf::Vector2f size = {60, 5};

        bool follow_element = true;

        float speed = .5f;
    };

public:
    
    UIHealthBar(const params& params);

    void Draw(sf::RenderWindow& window) override;
    void Update() override;

    sf::Transformable& GetTransform();
    const sf::Transformable& GetTransform() const;

    void SetPosition(sf::Vector2f position);

    float GetHeight() const override;
    float GetWidth() const override;

protected:
    ILife* _element;
    sf::Color _backgroundColor;
    sf::Color _mainColor;

    sf::RectangleShape _mainRectangle;
    sf::RectangleShape _backgroundRectangle;

    bool _followElement = true;
    float _currentScale = 0.f;

    //Scale/s
    float _speed = .5f;

    float _height, _width;

    virtual void UpdatePosition();

    sf::Transformable _transform;
};
