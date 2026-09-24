#include "UIHealthBar.h"

#include "Core/GameObject/IGameComponent/IGameComponent.h"
#include "Game/Time/Time.h"
#include "ILife/ILife.h"
#include "Other/Math/CMath.h"

UIHealthBar::UIHealthBar(
    const sf::Color backgroundColor, const sf::Color mainColor,
    const std::shared_ptr<ILife>& element, const sf::Vector2f size,
    const bool followElement
)
    : _element(element), _backgroundColor(backgroundColor), _mainColor(mainColor),
      _mainRectangle(size), _backgroundRectangle(size), _followElement(followElement), _width(size.x), _height(size.y)
{
    //Mettre l'origine en bas à gauche
    _backgroundRectangle.setOrigin({0, _backgroundRectangle.getGlobalBounds().size.y});
    _mainRectangle.setOrigin({0, _mainRectangle.getGlobalBounds().size.y});

    //Couleur des 
    _backgroundRectangle.setFillColor(_backgroundColor);
    _mainRectangle.setFillColor(_mainColor);
    
    // _mainRectangle.setPosition({0, 50});
    UIHealthBar::Update();
}

void UIHealthBar::Draw(sf::RenderWindow& window)
{
    window.draw(_backgroundRectangle);
    window.draw(_mainRectangle);
}

void UIHealthBar::Update()
{
    if (const auto& pourcent = _element->GetLifePourcent() / 100.0f;
        !CMath::floatEqual(pourcent, _currentScale))
    {
        const auto dt = (pourcent - _currentScale) / CMath::toPositif(pourcent - _currentScale) * _speed;
        _currentScale += dt * Time::deltaTime();
        if (dt > 0.0f)
            _currentScale = std::min(_currentScale, pourcent);
        else
            _currentScale = std::max(_currentScale, pourcent);
    }

    _mainRectangle.setScale({std::clamp(0.f, _currentScale, 1.f), 1});

    // UpdatePosition();
}

sf::Transformable& UIHealthBar::GetTransform()
{
    return _transform;
}

const sf::Transformable& UIHealthBar::GetTransform() const
{
    return _transform;
}

void UIHealthBar::SetPosition(const sf::Vector2f position)
{
    _mainRectangle.setPosition(position);
    _backgroundRectangle.setPosition(position);
}

float UIHealthBar::GetHeight() const
{
    return _height;
}

float UIHealthBar::GetWidth() const
{
    return _width;
}


void UIHealthBar::UpdatePosition()
{
    if (
        const auto pGameComponent = std::dynamic_pointer_cast<IGameComponent>(_element);
        pGameComponent != nullptr && _followElement
    )
    {
        auto position = pGameComponent->GetPosition();
        position.x -= _backgroundRectangle.getGlobalBounds().size.x / 2;
        position.y -= pGameComponent->GetBounds().size.y / 2.f + 10.f;
        SetPosition(position);
    }
}
