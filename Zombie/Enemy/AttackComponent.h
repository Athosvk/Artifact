#pragma once
#include <Artifact/Core/Component.h>

#include "../TimerComponent.h"

class AttackComponent : public Artifact::Component
{
private:
    TimerComponent* m_DelayTimer;
public:
    int Damage = 1;

public:
    AttackComponent(Artifact::GameObject a_GameObject);

    void setAttackInterval(float a_Interval);
    void startTimer();
    bool canAttack() const;
};

