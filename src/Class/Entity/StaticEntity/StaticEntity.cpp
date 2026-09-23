//
// Created by evant on 17/09/2026.
//

#include "StaticEntity.h"

#include "Character/BonusConsumer/BonusConsumer.h"
#include "Character/Player/Player.h"
#include "GameWindow/GameWindow.h"
#include  <iostream>
#include <memory>
#include <random>

#include "Game/Bonus/BaseBonus/BaseBonus.h"
#include "Game/Time/Time.h"
#include "Other/Math/CMath.h"

StaticEntity::StaticEntity(const sf::Texture& texture, const std::shared_ptr<BaseBonus>& projectileBonus,
    const std::shared_ptr<DamageBonus>& physiqueBonus)
    : BaseEntity(texture), _projectileBonus(projectileBonus), _physiqueBonus(physiqueBonus)
{
    float xpos = CMath::randf(-(static_cast<int>(WindowData::GetScreenSize().x / 2)), static_cast<int>(WindowData::GetScreenSize().x / 2));
    float ypos = CMath::randf(-(static_cast<int>(WindowData::GetScreenSize().x / 2)), static_cast<int>(WindowData::GetScreenSize().x / 2));

    _id = _count;
    _sprite.setScale({.15f, .15f});

    // _sprite.setOrigin({_sprite.getGlobalBounds().size.x / 2.f, _sprite.getGlobalBounds().size.y / 2.f});

    // SetPosition({static_cast<float>(std::rand()%WindowData::GetScreenSize().x), static_cast<float>(std::rand()%WindowData::GetScreenSize().y)});
    StaticEntity::SetPosition({xpos, ypos});
    _count++;
}

StaticEntity::StaticEntity(const char* texturePath,  const std::shared_ptr<BaseBonus>& projectileBonus,
    const std::shared_ptr<DamageBonus>& physiqueBonus)
    : BaseEntity(texturePath), _projectileBonus(projectileBonus), _physiqueBonus(physiqueBonus)
{
    _id = _count;
    _sprite.setScale({.15f, .15f});

    // _sprite.setOrigin({_sprite.getGlobalBounds().size.x / 2.f, _sprite.getGlobalBounds().size.y / 2.f});

    // SetPosition({static_cast<float>(std::rand()%WindowData::GetScreenSize().x), static_cast<float>(std::rand()%WindowData::GetScreenSize().y)});
    StaticEntity::SetPosition({0, 0});
    _count++;
}

sf::Vector2f StaticEntity::GetScaledSize() const
{
    const auto& scale = this->_sprite.getScale();
    const auto& size = this->_sprite.getLocalBounds().size;

    return {scale.x * size.x, scale.y * size.y};
}

void StaticEntity::Collision(const std::shared_ptr<IGameComponent>& otherComponent)
{
    BaseEntity::Collision(otherComponent);
    std::cout << "ok y'a une collision la\n";
    if (
        const auto pBonusConsumer = std::dynamic_pointer_cast<IBonusConsumer>(otherComponent);
        pBonusConsumer != nullptr
    )
    {
        std::cout << "Static Entity " << this->_id + 1 << " : Collision avec un bonus consumer\n";
        pBonusConsumer->GetBonusConsumer()->AddBonus(_projectileBonus);
        Destruct();
    }
}

void StaticEntity::Destruct() {
    // _factory->DeleteStaticEntity(this);
    SetMustDie();
}


