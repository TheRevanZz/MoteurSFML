//
// Created by sylvi on 12/09/2026.
//

#ifndef R5A12_PLAYER_H
#define R5A12_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Class/GameWindow/GameWindow.h"
#include "Interfaces/IDraweable/IDrawable.h"
#include "Interfaces/IUpdateable/IUpdateable.h"


class Player : public IUpdateable, public IDrawable {

public:
    explicit Player(const sf::Texture& texture, const sf::Vector2u& screenSize);

    const sf::Sprite& getSprite() const { return this->_sprite; }

    void handleEvent(const std::optional<sf::Event>& event);

    void setPosition(const WorldPoint& newPosition);

    sf::Vector2f getSize() const { return this->_sprite.getLocalBounds().size; }
    sf::Vector2f getScaledSize() const;
    sf::Vector2f getPosition() const { return this->_sprite.getPosition(); }

    void move(const sf::Vector2f& offset);

    explicit operator sf::Sprite() const { return this->_sprite; }

    void update() override;

    const sf::Drawable& getDrawable() const override {
        return this->_sprite;
    }

protected:
    sf::Sprite _sprite;
    WorldPoint _position;
    sf::Vector2u _screenSize;

    float _velocityX = 0.f;
    float _velocityY = 0.f;
    float _mass = 1.f;
    float _maxSpeed = 300.f;
    float _friction = 0.95f;
    float _thrustForce = 300.f;

private:
    void handleMovement();
};


#endif //R5A12_PLAYER_H