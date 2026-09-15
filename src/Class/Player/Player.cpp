//
// Created by sylvi on 12/09/2026.
//

#include "Player.h"
#include "Time/Time.h"
#include <fstream>
#include <iostream>
#include <ryml.hpp>
#include <ryml_std.hpp>
#include "Utils/Utils.h"


Player::Player(const sf::Texture &texture, const sf::Vector2u &screenSize)
    : IBaseCharacter(texture, 150), _screenSize(screenSize) {
    _sprite.setScale({.3f, .3f});
    _id = _count;

    if (_id == 0) {
        _keymapPath = "ressources/config/keymap1.yml";
        LoadKeymap(_keymapPath);
    } else {
        _keymapPath = "ressources/config/keymap2.yml";
        LoadKeymap(_keymapPath);
    }
    // keymap.at("Left").second = sf::Keyboard::Key::Left;
    _count++;
}

void Player::setPosition(const WorldPoint &newPosition) {
    _position = newPosition;
    _sprite.setPosition(sf::Vector2f(GameWindow::toScreenPoint(newPosition, _screenSize)));
}

sf::Vector2f Player::getScaledSize() const {
    const auto &scale = this->_sprite.getScale();
    const auto &size = this->_sprite.getLocalBounds().size;

    return {scale.x * size.x, scale.y * size.y};
}

void Player::move(const sf::Vector2f &offset) {
    //Si offset.length = offset.x c'est équivalent à ce que offset.y soit egal a 0.
    // offset.length c'est Vx**2 + y**2 donc si Vx**2 + y**2 = 0 alors c'est que y = 0 car Vx**2 + 0 = x
    _sprite.move({offset.x, -offset.y});
}

void Player::update(sf::RenderWindow &window) {
    handleMovement();
    // window.draw(this->_sprite);
}

void Player::handleMovement() {
    const auto &dt = Time::deltaTime();
    auto offset = sf::Vector2f(0, 0);
    if (
        PlayerIsDoingAction(EActionTag::LEFT)
    ) {
        offset.x -= 1;
    }
    if (PlayerIsDoingAction(EActionTag::RIGHT)) {
        offset.x += 1;
    }
    if (PlayerIsDoingAction(EActionTag::UP)) {
        // Up key pressed.
        offset.y += 1;
    }
    if (PlayerIsDoingAction(EActionTag::DOWN)) {
        // Down key pressed.
        offset.y -= 1;
    }

    if (offset.length() > 0) {
        //Le vecteur est normalisé comme ça la valeur de length est toujours égal a 1, donc les déplacements sont toujours de même vitesse
        // même en diagonale
        offset = offset.normalized();
        move(offset * _speed * dt);
    }
}

bool Player::PlayerIsDoingAction(EActionTag action_tag) const {
    auto KeymapValue = keymap.get(action_tag);
    if (!KeymapValue.has_value())
        return false;
    if (!KeymapValue.value().second.has_value())
        return false;
    return sf::Keyboard::isKeyPressed(KeymapValue.value().second.value());
}

bool Player::LoadKeymap(const std::string &keymapPath) {
    const auto &content = Utils::getFileContent(keymapPath);
    if (!content.has_value())
        return false;

    ryml::Tree YamlContent = ryml::parse_in_arena(c4::to_csubstr(content.value()));

    const auto touches = YamlContent["touches"];

    for (const std::string_view &key: GetEActionTagsValues()) {
        const auto keyStr = std::string(key);
        const auto &keyTag = StringToEActionTag(keyStr);
        if (!keyTag.has_value())
            continue;

        //Le code de la touche ( ex: 25 -> Z)
        const ryml::csubstr KeyCodeCSubStr = touches[keyStr.c_str()].val();

        try {
            int KeyCode = std::stoi(Utils::csubtrToString(KeyCodeCSubStr));

            auto OptionalKeymapValue = keymap.get(keyTag.value());
            if (!OptionalKeymapValue.has_value())
                return false;

            auto KeymapValue = OptionalKeymapValue.value();
            KeymapValue.second = static_cast<sf::Keyboard::Key>(KeyCode);

            keymap.update(keyTag.value(), KeymapValue);
        } catch (...) {
            std::cout << "Une erreur à lieu lors du chargement pour la clé" << keyStr << "\n";
        }
    }

    std::cout << "[KEYMAP] Keymap " << keymapPath << " loaded\n";

    return true;
}

bool Player::ChangeKey(const EActionTag &action_tag, const sf::Keyboard::Key &new_key) {
    auto OptionalValue = keymap.get(action_tag);
    if (!OptionalValue.has_value())
        return false;


    auto [keyDisplayName, KeyValue] = OptionalValue.value();
    KeyValue = new_key;

    keymap.update(action_tag, {keyDisplayName, KeyValue});

    const auto &content = Utils::getFileContent(_keymapPath);
    if (!content.has_value())
        return false;

    ryml::Tree YamlContent = ryml::parse_in_arena(
        ryml::to_csubstr(content.value())
    );

    const auto &action_tag_str = EActionTagToString(action_tag);

    if (!action_tag_str.has_value())
        return false;

    YamlContent["touches"][action_tag_str.value().c_str()] << static_cast<int>(new_key);

    std::ofstream config_file(_keymapPath);
    if (!config_file.is_open())
        return false;

    FILE *yamlFile;
    yamlFile = fopen(_keymapPath.c_str(), "w");

    if (yamlFile == nullptr)
        return false;

    ryml::emit_yaml(YamlContent, yamlFile);
    std::cout << "[KEYMAP] Keymap " << _keymapPath << " updated\n";
    return true;
}
