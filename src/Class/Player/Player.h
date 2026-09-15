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

        void setPosition(const WorldPoint& newPosition);
        
        sf::Vector2f getSize() const { return this->_sprite.getLocalBounds().size; }
        sf::Vector2f getScaledSize() const;
        sf::Vector2f getPosition() const { return this->_sprite.getPosition(); }
    
        void move(const sf::Vector2f& offset);
        void rotate(float angle);
        void progressiveRotate(float targetAngle);

        explicit operator sf::Sprite() const { return this->_sprite; }
    
        void update(sf::RenderWindow& window) override;
        const sf::Drawable* getDrawable() const override { return &this->_sprite;}
        

    protected:
        sf::Sprite _sprite; //par défaut dirigé vers la droite
        WorldPoint _position;
        sf::Vector2u _screenSize;
        float _speed = 160.f; //pixel par seconde;
        float _rotateSpeed = 500.f;
        sf::FloatRect _bounds;
        float _targetRotation = 0.f;
    
    private:
        void handleMovement();
        void handleRotation();
};


#endif //R5A12_PLAYER_H
