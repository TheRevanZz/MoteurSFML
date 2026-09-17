//
// Created by sylvi on 15/09/2026.
//

#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

enum class EBonusCategory {
    SPEED,
    DAMAGE,
    DASH,
    HEAL
};

enum class EBonusType {
    POURCENTAGE,
    DIRECT
};

#define BONUS_CONSTRUCTOR_ARGS \
    const float bonus, \
    const EBonusCategory bonusCategory, \
    const bool cumulable = true

class BaseBonus {

public:
    virtual ~BaseBonus() = default;

    explicit BaseBonus(
        BONUS_CONSTRUCTOR_ARGS
    ) : _bonus(bonus), _cumulable(cumulable), _bonusCategory(bonusCategory) {}

    virtual float getApplyedBonus(float value) const = 0;
    virtual void start() { _clock.start(); }

    bool bonusIsElapsed() const {
        const auto& elapsedTime = _clock.getElapsedTime();
        if (_life == 0)
            return false;
        return elapsedTime.asSeconds() > _life;
    }

    bool IsCumulable() const { return _cumulable; }
    const EBonusCategory& getBonusCategory() const { return _bonusCategory; }

protected:
    //Valeur du bonus
    float _bonus = 0;

    /*
     * Durée du bonus en seconde, 0 = infini
     */
    float _life = 10;
    sf::Clock _clock;

    bool _cumulable;
    EBonusCategory _bonusCategory;
};

class PourcentageBonus : public BaseBonus {

public:
    explicit PourcentageBonus(BONUS_CONSTRUCTOR_ARGS)
        : BaseBonus(bonus, bonusCategory ,cumulable) {}

    float getApplyedBonus(const float value) const override {
        return value * (1 + _bonus / 100);
    }
};

class DirectBonus : public BaseBonus {

public:
    explicit DirectBonus(BONUS_CONSTRUCTOR_ARGS)
        : BaseBonus(bonus, bonusCategory, cumulable) {}

    float getApplyedBonus(const float value) const override {
        return value + _bonus;
    }
};