#pragma once
#include <BadEngine/Core/Component.h>

#include "../TimerComponent.h"

class AttackComponent : public BadEngine::Component
{
private:
    TimerComponent* m_DelayTimer;
public:
    int Damage = 1;

public:
    AttackComponent(BadEngine::GameObject a_GameObject);

    void setAttackInterval(float a_Interval);
    void startTimer();
    bool canAttack() const;
};

