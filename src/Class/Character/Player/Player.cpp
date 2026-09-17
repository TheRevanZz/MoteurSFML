//
// Created by sylvi on 12/09/2026.
//

#include <fstream>
#include <iostream>
#include <ryml.hpp>
#include <ryml_std.hpp>

#include "Player.h"

#include <ranges>

#include "Debug.h"
#include "Game/Utils/Utils.h"
#include "Game/WindowData/WindowData.h"
#include "Game/Time/Time.h"


Player::Player(const sf::Texture& texture)
    : BaseCharacter(texture, 150), _screenSize(WindowData::getScreenSize())
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
}

void Player::setPosition(const WorldPoint& newPosition)
{
    _position = newPosition;
    _sprite.setPosition(sf::Vector2f(GameWindow::toScreenPoint(newPosition, _screenSize)));
}

sf::Vector2f Player::getScaledSize() const
{
    const auto& scale = this->_sprite.getScale();
    const auto& size = this->_sprite.getLocalBounds().size;

    return {scale.x * size.x, scale.y * size.y};
}

const sf::Transform Player::getTransform() const
{
    return this->_sprite.getTransform();
}

void Player::move(const sf::Vector2f& offset)
{
    //Si offset.length = offset.x c'est équivalent à ce que offset.y soit egal a 0.
    // offset.length c'est Vx**2 + y**2 donc si Vx**2 + y**2 = 0 alors c'est que y = 0 car Vx**2 + 0 = x
    _sprite.move({offset.x, -offset.y});

    //si à droite de l'écran
    if (_sprite.getPosition().x > _screenSize.x - getScaledSize().x / 2)
    {
        //remplacer par une force
        _sprite.setPosition(sf::Vector2f(_screenSize.x - getScaledSize().x / 2, _sprite.getPosition().y));
    }
    //si à gauche de l'écran
    if (_sprite.getPosition().x < 0 + getScaledSize().x / 2)
    {
        //remplacer par une force
        _sprite.setPosition(sf::Vector2f(0 + getScaledSize().x / 2, _sprite.getPosition().y));
    }
    //si en bas de l'écran
    if (_sprite.getPosition().y > _screenSize.y - getScaledSize().y / 2)
    {
        //remplacer par une force
        _sprite.setPosition(sf::Vector2f(_sprite.getPosition().x, _screenSize.y - getScaledSize().y / 2));
    }
    //si en haut de l'écran
    if (_sprite.getPosition().y < 0 + getScaledSize().y / 2)
    {
        //remplacer par une force
        _sprite.setPosition(sf::Vector2f(_sprite.getPosition().x, 0 + getScaledSize().y / 2));
    }
}

void Player::rotate(float angle)
{
    _sprite.rotate(sf::degrees(angle));
}

void Player::progressiveRotate(float targetAngle)
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

        rotate(tempRotation);
    }
    else if (angle < 0.f)
    {
        if (_rotateSpeed * dt < -angle)
            tempRotation = _rotateSpeed * dt;
        else
            tempRotation = -angle;

        rotate(-tempRotation);
    }
}

void Player::update()
{
    handleMovement();
    handleRotation();
    progressiveRotate(_targetRotation);
}

void Player::handleMovement()
{
    const auto& dt = Time::deltaTime();
    auto offset = sf::Vector2f(0, 0);
    if (
        PlayerIsDoingAction(EActionTag::LEFT)
    )
    {
        offset.x -= 1;
    }
    if (PlayerIsDoingAction(EActionTag::RIGHT))
    {
        offset.x += 1;
    }
    if (PlayerIsDoingAction(EActionTag::UP))
    {
        // Up key pressed.
        offset.y += 1;
    }
    if (PlayerIsDoingAction(EActionTag::DOWN))
    {
        // Down key pressed.
        offset.y -= 1;
    }

    DEBUG_ONLY(
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
        std::cout << applyBonusToStat(_speed, EBonusCategory::SPEED) << "\n";
        std::cout << _speed << "\n";
        }
    )

    if (offset.length() > 0)
    {
        //Le vecteur est normalisé comme ça la valeur de length est toujours égal a 1, donc les déplacements sont toujours de même vitesse
        // même en diagonale
        offset = offset.normalized();
        move(offset * applyBonusToStat(_speed, EBonusCategory::SPEED) * dt);
    }
}


bool Player::PlayerIsDoingAction(const EActionTag action_tag) const
{
    const auto KeymapValue = keymap.get(action_tag);
    if (!KeymapValue.has_value())
        return false;
    if (!KeymapValue.value().second.has_value())
        return false;
    return sf::Keyboard::isKeyPressed(KeymapValue.value().second.value());
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

            auto OptionalKeymapValue = keymap.get(keyTag.value());
            if (!OptionalKeymapValue.has_value())
                return false;

            auto KeymapValue = OptionalKeymapValue.value();
            KeymapValue.second = static_cast<sf::Keyboard::Key>(KeyCode);

            keymap.update(keyTag.value(), KeymapValue);
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
    auto OptionalValue = keymap.get(action_tag);
    if (!OptionalValue.has_value())
        return false;


    auto [keyDisplayName, KeyValue] = OptionalValue.value();
    KeyValue = new_key;

    keymap.update(action_tag, {keyDisplayName, KeyValue});

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
    std::cout << "[KEYMAP] Keymap " << _keymapPath << " updated\n";
    if (int returnCode = fclose(yamlFile); returnCode == EOF)
    {
        DEBUG_ONLY(
            std::cerr << "ERREUR DANS LA FERMETURE DU FICHIER\n"
        );
        exit(-1);
    }
    return true;
}

void Player::Collision(const std::shared_ptr<IGameComponent>& otherComponent) const
{
    IGameComponent::Collision(otherComponent);
    if (std::dynamic_pointer_cast<StaticEntity>(otherComponent))
    {
        auto pEntity = std::dynamic_pointer_cast<StaticEntity>(otherComponent);
        std::cout << "Joueur " << this->_id + 1 << " : Collision avec StaticEntity" << pEntity->getId() + 1 << std::endl;
    }
    // abort();
}

float Player::applyBonusToStat(const float& stat, const EBonusCategory bonusCategory) const
{
    auto _targetBonuses = _bonuses | std::views::filter([bonusCategory](const auto& bonus)
    {
        return bonus->getBonusCategory() == bonusCategory;
    });

    if (_targetBonuses.empty())
        return stat;

    float final_stat = (*_targetBonuses.begin())->getApplyedBonus(stat);
    auto it = _targetBonuses.begin();
    ++it;
    for (; it != _targetBonuses.end(); ++it)
    {
        final_stat = (*it)->getApplyedBonus(final_stat);
    }
    return final_stat;
}

void Player::handleRotation()
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
}
