//
// Created by sylvi on 12/09/2026.
//
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_set>

#include "Other/LockedMap/LockedMap.h"

#include "Character/BaseCharacter/BaseCharacter.h"
#include "Character/BonusConsumer/BonusConsumer.h"
#include "Component/MultipleSprite/MultipleSpriteComponent.h"
#include "Enum/EBonusCategory.h"
#include "Enum/EKeyTag.h"


//Description de la touche
using KeyDisplayName = std::string;

constexpr int PLAYER_LIFE = 150;
/*
 Contient la description de la touche, ainsi que optionnelle le code de la touche elle même
 */
using KeyValue = std::pair<
    KeyDisplayName,
    std::optional<sf::Keyboard::Key>
>;

class Player : public BaseCharacter, public BonusConsumer {

public:
    static int _count;

    explicit Player(std::vector<const char *> texturesPaths, uint8_t textureIndex = 0);
    explicit Player(std::vector<std::string> texturesPaths, uint8_t textureIndex = 0);
    
    int GetId() const { return this->_id; }
    
    const sf::Sprite& GetSprite() const { return this->_sprite; }
    
    sf::Vector2f GetSize() const { return this->_sprite.getLocalBounds().size; }

    sf::Vector2f GetScaledSize() const;

    const sf::Vector2f GetPosition() const override { return this->_sprite.getPosition(); }
    const sf::FloatRect GetBounds() const override { return this->_sprite.getGlobalBounds(); }
    const sf::Transform GetTransform() const override;

    void Move(const sf::Vector2f& offset);


    void Rotate(float angle);
    void ProgressiveRotate(float targetAngle);

    explicit operator sf::Sprite() const { return this->_sprite; }

    void update() override;

    const sf::Drawable& getDrawable() const override { return this->_sprite; }

    [[nodiscard("Il faut vérifier si l'opération a réussi")]]
    bool LoadKeymap(const std::string& keymapPath);

    /**
     * Méthode permettant de changer les touches du joueur
     * @param action_tag - L'action voulant être changer
     * @param new_key - La nouvelle clé lui étant associé
     * @return false si l'opération à échouée, true sinon
     */
    [[nodiscard("Il faut vérifier si l'opération a réussi")]]
    bool ChangeKey(const EActionTag& action_tag, const sf::Keyboard::Key& new_key);

    void takeDamage(const float& damage) override { this->_life -= damage; }

    void Collision(const std::shared_ptr<IGameComponent> &otherComponent) override;
    void Destruct() override
    {
        // auto pAssetLoader = AssetLoader::getInstance();
        // _sprite.setTexture(*pAssetLoader->getImage("ressources/images/player_textures/spaceship_1.png"));
        // multipleSpriteComponent.changeTexture(0u);
    }
    
    void ChangeSprite(uint8_t id);

private:
    float ApplyBonusToStat(const float& stat, EBonusCategory bonusCategory) const;

protected:
    std::vector<const char*> _texturesPaths;
    CoordinateSystem::WorldPoint _position;
    sf::Vector2u _screenSize;
    float _speed = 160.f; //pixel par seconde;
    
    float _velocityX = 0.f;
    float _velocityY = 0.f;
    float _mass = 1.f;
    float _maxSpeed = 150.f;
    float _friction = 0.90f;
    float _thrustForce = 500.f;
    
    int _id = 0;
    std::string _keymapPath = "ressources/config/keymap1.yml";

    LockedMap<EActionTag, KeyValue> _keymap = LockedMap<EActionTag, KeyValue>({
        {EActionTag::RIGHT, {"Aller à droite", {}}},
        {EActionTag::LEFT, {"Aller à gauche", {}}},
        {EActionTag::UP, {"Aller en haut", {}}},
        {EActionTag::DOWN, {"Aller en bas", {}}},
        {EActionTag::DASH, {"Dash", {}}}
    });
    
    float _rotateSpeed = 500.f;
    float _targetRotation = 0.f;
    
    MultipleSpriteComponent _multipleSpriteComponent;

private:
    void HandleMovement();
    void HandleRotation();
    bool PlayerIsDoingAction(EActionTag action_tag) const;
    void Init();
};

inline int Player::_count = 0;
