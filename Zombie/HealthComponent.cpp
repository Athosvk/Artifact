#include <Artifact/MathHelper.h>

#include "HealthComponent.h"

HealthComponent::HealthComponent(Artifact::GameObject a_GameObject)
    : Component(a_GameObject)
{
}

void HealthComponent::initialise(unsigned a_MaxHealth)
{
    MaxHealth = a_MaxHealth;
    m_CurrentHealth = a_MaxHealth;
}

void HealthComponent::dealDamage(unsigned a_Amount)
{
    m_CurrentHealth = Artifact::MathHelper::max(m_CurrentHealth - a_Amount, 0u);
    OnHit();
    if(m_CurrentHealth == 0)
    {
        OnDeath(this);
    }
}

unsigned HealthComponent::getCurrentHealth() const
{
    return m_CurrentHealth;
}
