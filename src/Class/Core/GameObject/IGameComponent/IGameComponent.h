//
// Created by sylvi on 14/09/2026.
//

#pragma once
#include <memory>
#include <unordered_set>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "Game/CoordinateSystem/CoordinateSystem.h"
#include "IDraweable/IDrawable.h"


class IGameComponent : public IDrawable {

public:
    IGameComponent() = default;

    virtual sf::Vector2f GetPosition() const;
    virtual void SetPosition(const CoordinateSystem::WorldPoint& position);
    virtual sf::Transform GetTransform() const;
    
    virtual const sf::FloatRect GetBounds() const = 0;
    virtual const sf::Transformable& GetTransformable() const = 0;
    virtual sf::Transformable& GetTransformable() = 0;
    virtual void Draw(sf::RenderWindow& window);

    virtual void Collision(const std::shared_ptr<IGameComponent>& otherComponent);

    const bool& GetMustDie() const { return _mustDie; }
    void SetMustDie() { _mustDie = true; }
    
    virtual const std::pmr::unordered_set<char*>& GetTags() const ;
    
protected:
    bool _mustDie = false;
    std::pmr::unordered_set<char*> _tags = {};
};



