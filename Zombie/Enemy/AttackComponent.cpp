#include <Artifact/Core/EntitySystem.h>

#include "AttackComponent.h"

AttackComponent::AttackComponent(Artifact::GameObject a_GameObject)
    : Component(a_GameObject)
{
    m_DelayTimer = addComponent<TimerComponent>();
}

void AttackComponent::setAttackInterval(float a_Interval)
{
    m_DelayTimer->Duration = a_Interval;
}

void AttackComponent::startTimer()
{
    m_DelayTimer->start();
}

bool AttackComponent::canAttack() const
{
    return m_DelayTimer->TimerState == ETimerState::Done;
}
