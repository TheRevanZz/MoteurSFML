//
// Created by sylvi on 12/09/2026.
//
#pragma once

#include <map>
#include <ranges>
#include <SFML/Graphics.hpp>

#include "Class/GameWindow/GameWindow.h"
#include "LockedMap/LockedMap.h"
#include <string>

#include "BaseCharacter/BaseCharacter.h"
#include "BonusConsumer/BonusConsumer.h"
#include "Enum/EBonusCategory.h"
#include "Enum/EKeyTag.h"


//Description de la touche
using KeyDisplayName = std::string;

/*
 Contient la description de la touche, ainsi que optionnelle le code de la touche elle même
 */
using KeyValue = std::pair<
    KeyDisplayName,
    std::optional<sf::Keyboard::Key>
>;

class Player : public BaseCharacter, BonusConsumer {

public:
    static int _count;

    explicit Player(const sf::Texture &texture, const sf::Vector2u &screenSize);

    const sf::Sprite &getSprite() const { return this->_sprite; }

    void setPosition(const WorldPoint &newPosition);

    sf::Vector2f getSize() const { return this->_sprite.getLocalBounds().size; }

    sf::Vector2f getScaledSize() const;

    const sf::Vector2f getPosition() const override { return this->_sprite.getPosition(); }
    const sf::FloatRect getBounds() const override { return this->_sprite.getGlobalBounds(); }
    const sf::Transform getTransform() const override;

    void move(const sf::Vector2f &offset);
        
        
        void rotate(float angle);
        void progressiveRotate(float targetAngle);

    explicit operator sf::Sprite() const { return this->_sprite; }

    void update() override;

    const sf::Drawable& getDrawable() const override { return this->_sprite; }

    [[nodiscard("Il faut vérifier si l'opération a réussi")]]
    bool LoadKeymap(const std::string &keymapPath);

    /**
     * Méthode permettant de changer les touches du joueur
     * @param action_tag - L'action voulant être changer
     * @param new_key - La nouvelle clé lui étant associé
     * @return false si l'opération à échouée, true sinon
     */
    [[nodiscard("Il faut vérifier si l'opération a réussi")]]
    bool ChangeKey(const EActionTag& action_tag, const sf::Keyboard::Key& new_key);

    void takeDamage(const int &damage) override { this->_life -= damage; }
    bool IsDead() const override { return this->_life <= 0; }
    void Destruct() override {}

    void Collision(const std::shared_ptr<IGameComponent> &otherComponent) const override;

private:
    float applyBonusToStat(const float& stat, EBonusCategory bonusCategory) const;

protected:

    WorldPoint _position;
    sf::Vector2u _screenSize;
    float _speed = 160.f; //pixel par seconde;
    int _id = 0;
    std::string _keymapPath = "ressources/config/keymap1.yml";

    LockedMap<EActionTag, KeyValue> keymap = LockedMap<EActionTag, KeyValue>({
        {EActionTag::RIGHT, {"Aller à droite", {}}},
        {EActionTag::LEFT, {"Aller à gauche", {}}},
        {EActionTag::UP,{"Aller en haut", {}}},
        {EActionTag::DOWN, {"Aller en bas", {}}},
        {EActionTag::DASH, {"Dash", {}}}
    });
    
    float _rotateSpeed = 500.f;
    sf::FloatRect _bounds;
    float _targetRotation = 0.f;

private:
    void handleMovement();
    void handleRotation();
    bool PlayerIsDoingAction(EActionTag action_tag) const;
};

inline int Player::_count = 0;