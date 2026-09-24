#pragma once

#define BONUS_CONSTRUCTOR_ARGS \
    const float bonus, \
    const EBonusCategory bonusCategory, \
    const bool cumulable = true, \
    const float life = 10


class BonusConsumer;
enum class EBonusCategory;

class BaseBonus {

public:
    virtual ~BaseBonus() = default;

    explicit BaseBonus(
        BONUS_CONSTRUCTOR_ARGS
    ) : _bonus(bonus), _cumulable(cumulable), _bonusCategory(bonusCategory), _life(life) {}

    virtual float GetApplyedBonus(float value) const = 0;

    bool IsElapsed() const;
    
    void UpdateTimer();

    bool IsCumulable() const;
    const EBonusCategory& GetBonusCategory() const;

protected:
    //Valeur du bonus
    float _bonus = 0;

    /*
     * Durée du bonus en seconde, 0 = infini
     */
    float _life = 10;
    float _timer = 0.0f;

    bool _cumulable;
    EBonusCategory _bonusCategory;
};