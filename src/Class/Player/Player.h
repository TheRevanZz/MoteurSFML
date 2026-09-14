//
// Created by sylvi on 12/09/2026.
//
#pragma once


#include <map>
#include <SFML/Graphics.hpp>

#include "Class/GameWindow/GameWindow.h"
#include "Interfaces/IDraweable/IDrawable.h"
#include "Interfaces/IUpdateable/IUpdateable.h"
#include "LockedMap/LockedMap.h"
#include <string>

#include "Enum/EKeyTag.h"
#include "GameComponent/GameComponent.h"


//Description de la touche
using KeyDisplayName = std::string;

/*
 Contient la description de la touche, ainsi que optionnelle le code de la touche elle même
 */
using KeyValue = std::pair<
    KeyDisplayName,
    std::optional<sf::Keyboard::Key>
>;

class Player : public GameComponent, public IUpdateable {

public:
    static int _count;

    explicit Player(const sf::Texture &texture, const sf::Vector2u &screenSize);

    const sf::Sprite &getSprite() const { return this->_sprite; }

    void setPosition(const WorldPoint &newPosition);

    sf::Vector2f getSize() const { return this->_sprite.getLocalBounds().size; }

    sf::Vector2f getScaledSize() const;

    sf::Vector2f getPosition() const { return this->_sprite.getPosition(); }

    void move(const sf::Vector2f &offset);

    explicit operator sf::Sprite() const { return this->_sprite; }

    void update(sf::RenderWindow &window) override;

    const sf::Drawable *getDrawable() const override { return &this->_sprite; }

    bool LoadKeymap(const std::string &keymapPath);

    /**
     * Méthode permettant de changer les touches du joueur
     * @param action_tag - L'action voulant être changer
     * @param new_key - La nouvelle clé lui étant associé
     * @return false si l'opération à échouée, true sinon
     */
    bool ChangeKey(const EActionTag& action_tag, const sf::Keyboard::Key& new_key);

protected:
    sf::Sprite _sprite;
    WorldPoint _position;
    sf::Vector2u _screenSize;
    float _speed = 160.f; //pixel par seconde;
    int _id = 0;
    std::string _keymapPath = "ressources/config/keymap1.yml";

    LockedMap<EActionTag, KeyValue> keymap = LockedMap<EActionTag, KeyValue>({
        {EActionTag::RIGHT, {"Aller à droite", {}}},
        {EActionTag::LEFT, {"Aller à gauche", {}}},
        {EActionTag::UP, {"Aller en haut", {}}},
        {EActionTag::DOWN, {"Aller en bas", {}}},
        {EActionTag::DASH, {"Dash", {}}}
    });

private:
    void handleMovement();

protected:
};

inline int Player::_count = 0;