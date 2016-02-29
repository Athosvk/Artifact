#include <BadEngine/MathHelper.h>

#include "HealthComponent.h"

HealthComponent::HealthComponent(BadEngine::GameObject a_GameObject)
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
    m_CurrentHealth = BadEngine::MathHelper::max(m_CurrentHealth - a_Amount, 0u);
    if(m_CurrentHealth == 0)
    {
        OnDeath(this);
    }
}

unsigned HealthComponent::getCurrentHealth() const
{
    return m_CurrentHealth;
}
