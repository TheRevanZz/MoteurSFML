//
// Created by sylvi on 12/09/2026.
//

#include <fstream>
#include <iostream>
#include <ryml.hpp>
#include <ryml_std.hpp>
#include <ranges>
#include <utility>


#include "Player.h"
#include "Debug.h"
#include "Character/BonusConsumer/BonusConsumer.h"
#include "Game/Utils/Utils.h"
#include "Game/WindowData/WindowData.h"
#include "Game/Time/Time.h"
#include "Class/Component/MultipleSprite/MultipleSpriteComponent.h"
#include "Class/Component/ShootComponent/ShootComponent.h"
#include "Entity/StaticEntity/StaticEntity.h"
#include "Class/Game/Bonus/BaseBonus/BaseBonus.h"
#include "Component/ShootComponent/Bullet.h"


void Player::Init()
{
    _id = _count;
    _sprite.setScale({.15f, .15f});

    if (_id == 0)
    {
        _keymapPath = "ressources/config/keymap1.yml";
    }
    else
    {
        _keymapPath = "ressources/config/keymap2.yml";
    }

    bool sucessLoading = LoadKeymap(_keymapPath);
    if (!sucessLoading)
        abort();
    // assert( sucessLoading == true && ("ERREUR DANS LE CHARGEMENT " + _keymapPath).c_str());
    // keymap.at("Left").second = sf::Keyboard::Key::Left;

    _sprite.setOrigin({_sprite.getLocalBounds().size.x / 2.f, _sprite.getLocalBounds().size.y / 2.f});
    _count++;
    // _sprite.setColor(sf::Color(255,0,0));
}

Player::HitAnimation Player::CreateHitAnimation()
{
    return {
        {
            {0,  [this] { ChangeSpriteColor(sf::Color::Red); }},
            {15, [this] { ChangeSpriteColor(sf::Color::White); }},
            {30, [this] { ChangeSpriteColor(sf::Color::Red); }},
            {45, [this] { ChangeSpriteColor(sf::Color::White); }},
            {60, [this] { ChangeSpriteColor(sf::Color::Red); }},
            {75, [this] { ChangeSpriteColor(sf::Color::White); }}
        },
        [this] { _isBeingHit = false; },
        .5f
    };
}

Player::Player(std::vector<const char*> texturesPaths, const uint8_t textureIndex)
    : BaseCharacter(texturesPaths[textureIndex], PLAYER_LIFE),
      _screenSize(WindowData::GetScreenSize()),
      _pMultipleSpriteComponent(
          se3::CreateComponent<MultipleSpriteComponent>(
              this,
              texturesPaths,
              &_sprite,
              textureIndex)
      ),
      _pShootComponent(
          CreateComponent<ShootComponent>(this)
      ),
      _pBonusConsumer(CreateComponent<BonusConsumer>(this)),
      _hitAnimation(CreateHitAnimation())
{
    Init();
}

Player::Player(std::vector<std::string> texturesPaths, const uint8_t textureIndex)
    : BaseCharacter(texturesPaths[textureIndex].c_str(), PLAYER_LIFE),
      _screenSize(WindowData::GetScreenSize()),
      _pMultipleSpriteComponent(
          se3::CreateComponent<MultipleSpriteComponent>(
              this,
              texturesPaths,
              &_sprite,
              textureIndex
          )
      ),
      _pShootComponent(
          CreateComponent<ShootComponent>(this)
      ),
      _pBonusConsumer(CreateComponent<BonusConsumer>(this)),
      _hitAnimation(CreateHitAnimation())
{
    Init();
}

sf::Vector2f Player::GetScaledSize() const
{
    const auto& scale = this->_sprite.getScale();
    const auto& size = this->_sprite.getLocalBounds().size;

    return {scale.x * size.x, scale.y * size.y};
}

void Player::Move(const sf::Vector2f& offset)
{
    //Si offset.length = offset.x c'est équivalent à ce que offset.y soit egal a 0.
    // offset.length c'est Vx**2 + y**2 donc si Vx**2 + y**2 = 0 alors c'est que y = 0 car Vx**2 + 0 = x
    _sprite.move({offset.x, -offset.y});

    //si à droite de l'écran
    if (_sprite.getPosition().x > _screenSize.x - GetScaledSize().x / 2)
    {
        //remplacer par une force
        _sprite.setPosition(sf::Vector2f(_screenSize.x - GetScaledSize().x / 2, _sprite.getPosition().y));
    }
    //si à gauche de l'écran
    if (_sprite.getPosition().x < 0 + GetScaledSize().x / 2)
    {
        //remplacer par une force
        _sprite.setPosition(sf::Vector2f(0 + GetScaledSize().x / 2, _sprite.getPosition().y));
    }
    //si en bas de l'écran
    if (_sprite.getPosition().y > _screenSize.y - GetScaledSize().y / 2)
    {
        //remplacer par une force
        _sprite.setPosition(sf::Vector2f(_sprite.getPosition().x, _screenSize.y - GetScaledSize().y / 2));
    }
    //si en haut de l'écran
    if (_sprite.getPosition().y < 0 + GetScaledSize().y / 2)
    {
        //remplacer par une force
        _sprite.setPosition(sf::Vector2f(_sprite.getPosition().x, 0 + GetScaledSize().y / 2));
    }
}

CoordinateSystem::WorldPoint Player::GetBulletStartPosition() const
{
    const auto rotation = _sprite.getRotation().asRadians();
    const auto direction = sf::Vector2f(std::cos(rotation), std::sin(rotation)).normalized();
    const auto size = _sprite.getGlobalBounds().size;
    const auto add = sf::Vector2f{size.x * direction.x / 2, size.y * direction.y / 2};
    return {_sprite.getPosition().x + add.x, _sprite.getPosition().y + add.y};
}

void Player::Shoot()
{
    _pShootComponent->Shoot();
}

void Player::Rotate(float angle)
{
    _sprite.rotate(sf::degrees(angle));
}

void Player::ProgressiveRotate(float targetAngle)
{
    const auto& dt = Time::deltaTime();

    const float currentAngle = _sprite.getRotation().asDegrees();
    // pr atteindre le target angle je dois rotate de angle°
    float angle = targetAngle - currentAngle;

    //normalise entre -180 et 180
    while (angle > 180.f)
    {
        angle -= 360.f;
    }
    while (angle < -180.f)
    {
        angle += 360.f;
    }

    float tempRotation;
    if (angle > 0.f)
    {
        if (_rotateSpeed * dt < angle)
            tempRotation = _rotateSpeed * dt;
        else
            tempRotation = angle;

        Rotate(tempRotation);
    }
    else if (angle < 0.f)
    {
        if (_rotateSpeed * dt < -angle)
            tempRotation = _rotateSpeed * dt;
        else
            tempRotation = -angle;

        Rotate(-tempRotation);
    }
}

void Player::update()
{
    HandleMovement();
    HandleRotation();
    ProgressiveRotate(_targetRotation);
    _pBonusConsumer->UpdateBonusesTimers();
    if (_isBeingHit)
    {
        _hitAnimation.Animate();
    }
}

void Player::ChangeSpriteColor(const sf::Color newColor)
{
    _sprite.setColor(newColor);
}

void Player::HandleMovement()
{
    const float dt = Time::deltaTime();

    //calcul forces selon input
    sf::Vector2f input(0.f, 0.f);
    if (PlayerIsDoingAction(EActionTag::LEFT))
    {
        input.x -= 1.f;
    }
    if (PlayerIsDoingAction(EActionTag::RIGHT))
    {
        input.x += 1.f;
    }
    if (PlayerIsDoingAction(EActionTag::UP))
    {
        input.y += 1.f;
    }
    if (PlayerIsDoingAction(EActionTag::DOWN))
    {
        input.y -= 1.f;
    }

    // calcul forces
    float forceX = 0.f;
    float forceY = 0.f;

    if (input.length() > 0.f)
    {
        input = input.normalized();

        // application de la force dans la direction indiquee par le joueur
        forceX = input.x * _thrustForce;
        forceY = input.y * _thrustForce;
    }

    // euler velocity: v_{n+1} = v_n + (F/m) * dt

    // acceleration: a = F / m
    float accelerationX = forceX / _mass;
    float accelerationY = forceY / _mass;

    // update velocity
    _velocityX += accelerationX * dt;
    _velocityY += accelerationY * dt;

    // deceleration
    // approximation discrète : v(n+1) = friction * v(n)
    // cela simule une diminution exponentielle de la vitesse
    if (input.length() == 0.f)
    {
        _velocityX *= _friction;
        _velocityY *= _friction;
    }

    // limitation de la vitesse maximale
    const float speed = std::sqrt(_velocityX * _velocityX + _velocityY * _velocityY);

    if (
        const float maxSpeed = ApplyBonusToStat(_maxSpeed, EBonusCategory::SPEED);
        speed > maxSpeed
    )
    {
        const float scale = maxSpeed / speed;
        _velocityX *= scale;
        _velocityY *= scale;
    }

    // methode d'Euler pour calculer la position :
    // x(n+1) = x(n) + v(n) * dt
    // cela correspond à l'approximation discrète de dx/dt = v
    const sf::Vector2f displacement(_velocityX * dt, _velocityY * dt);
    Move(displacement);
}


bool Player::PlayerIsDoingAction(const EActionTag action_tag) const
{
    const auto keymapValue = _keymap.get(action_tag);
    if (!keymapValue.has_value())
        return false;
    if (!keymapValue.value().second.has_value())
        return false;
    return sf::Keyboard::isKeyPressed(keymapValue.value().second.value());
}

bool Player::LoadKeymap(const std::string& keymapPath)
{
    const auto& content = Utils::getFileContent(keymapPath);
    if (!content.has_value())
        return false;

    ryml::Tree YamlContent = ryml::parse_in_arena(c4::to_csubstr(content.value()));

    if (!YamlContent.rootref().is_map())
    {
        abort();
    }
    const auto touches = YamlContent["touches"];

    for (const std::string_view& key : GetEActionTagsValues())
    {
        const auto keyStr = std::string(key);
        const auto& keyTag = StringToEActionTag(keyStr);
        if (!keyTag.has_value())
            continue;

        //Le code de la touche ( ex: 25 -> Z)
        const ryml::csubstr KeyCodeCSubStr = touches[keyStr.c_str()].val();

        try
        {
            int KeyCode = std::stoi(Utils::csubtrToString(KeyCodeCSubStr));

            auto OptionalKeymapValue = _keymap.get(keyTag.value());
            if (!OptionalKeymapValue.has_value())
                return false;

            auto KeymapValue = OptionalKeymapValue.value();
            KeymapValue.second = static_cast<sf::Keyboard::Key>(KeyCode);

            _keymap.update(keyTag.value(), KeymapValue);
        }
        catch (...)
        {
            DEBUG_ONLY(
                std::cout << "Une erreur à lieu lors du chargement pour la clé" << keyStr << "\n";
            )
        }
    }

    DEBUG_ONLY(
        std::cout << "[KEYMAP] Keymap " << keymapPath << " loaded\n";
    )
    return true;
}

bool Player::ChangeKey(const EActionTag& action_tag, const sf::Keyboard::Key& new_key)
{
    auto OptionalValue = _keymap.get(action_tag);
    if (!OptionalValue.has_value())
        return false;


    auto [keyDisplayName, KeyValue] = OptionalValue.value();
    KeyValue = new_key;

    _keymap.update(action_tag, {keyDisplayName, KeyValue});

    const auto& content = Utils::getFileContent(_keymapPath);
    if (!content.has_value())
        return false;

    ryml::Tree YamlContent = ryml::parse_in_arena(
        ryml::to_csubstr(content.value())
    );

    if (!YamlContent.rootref().is_map())
    {
        abort();
    }

    const auto& action_tag_str = EActionTagToString(action_tag);

    if (!action_tag_str.has_value())
        return false;

    YamlContent["touches"][action_tag_str.value().c_str()] << static_cast<int>(new_key);

    FILE* yamlFile = fopen(_keymapPath.c_str(), "w");

    if (yamlFile == nullptr)
        return false;

    ryml::emit_yaml(YamlContent, yamlFile);
    DEBUG_ONLY(
        std::cout << "[KEYMAP] Keymap " << _keymapPath << " updated\n";
    )
    if (int returnCode = fclose(yamlFile); returnCode == EOF)
    {
        DEBUG_ONLY(
            std::cerr << "ERREUR DANS LA FERMETURE DU FICHIER\n"
        );
        exit(-1);
    }
    return true;
}

void Player::Collision(const std::shared_ptr<IGameComponent>& otherComponent)
{
    // std::cout << "test collision\n";
    IGameComponent::Collision(otherComponent);
    if (std::dynamic_pointer_cast<StaticEntity>(otherComponent))
    {
        const auto pEntity = std::dynamic_pointer_cast<StaticEntity>(otherComponent);
        DEBUG_ONLY(
            std::cout << "Joueur " << this->_id + 1 << " : Collision avec StaticEntity" << pEntity->GetId() + 1 << "\n";
        )
    }
    if (auto bullet = std::dynamic_pointer_cast<Bullet>(otherComponent); bullet != nullptr)
    {
        _isBeingHit = true;
    }
    // abort();
}

void Player::ChangeSprite(const uint8_t id)
{
    _pMultipleSpriteComponent->ChangeTexture(id);
}

const std::shared_ptr<BonusConsumer>& Player::GetBonusConsumer() const
{
    return _pBonusConsumer;
}


float Player::ApplyBonusToStat(const float& stat, const EBonusCategory bonusCategory) const
{
    auto targetBonuses = _pBonusConsumer->GetBonuses() | std::views::filter([bonusCategory](const auto& bonus)
    {
        return bonus->GetBonusCategory() == bonusCategory;
    });

    if (targetBonuses.empty())
        return stat;

    float final_stat = (*targetBonuses.begin())->GetApplyedBonus(stat);
    auto it = targetBonuses.begin();
    ++it;
    for (; it != targetBonuses.end(); ++it)
    {
        final_stat = (*it)->GetApplyedBonus(final_stat);
    }
    return final_stat;
}

void Player::HandleRotation()
{
    if (PlayerIsDoingAction(EActionTag::LEFT))
    {
        _targetRotation = 180;
    }
    else if (PlayerIsDoingAction(EActionTag::RIGHT))
    {
        _targetRotation = 0;
    }
    if (PlayerIsDoingAction(EActionTag::UP))
    {
        // Up key pressed.
        _targetRotation = 270;
        if (PlayerIsDoingAction(EActionTag::LEFT))
        {
            _targetRotation -= 45.f;
        }
        else if (PlayerIsDoingAction(EActionTag::RIGHT))
        {
            _targetRotation += 45.f;
        }
    }
    else if (PlayerIsDoingAction(EActionTag::DOWN))
    {
        // Down key pressed.
        _targetRotation = 90;
        if (PlayerIsDoingAction(EActionTag::LEFT))
        {
            _targetRotation += 45.f;
        }
        else if (PlayerIsDoingAction(EActionTag::RIGHT))
        {
            _targetRotation -= 45.f;
        }
    }
    // std::cout << "rotation : " << _targetRotation << "\n";
}
