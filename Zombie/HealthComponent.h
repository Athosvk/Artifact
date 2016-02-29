#pragma once
#include <BadEngine/Core/Component.h>
#include <BadEngine/Delegate.h>

class HealthComponent : public BadEngine::Component
{
private:
    unsigned m_CurrentHealth;
public:
    unsigned MaxHealth;
    Delegate<void(HealthComponent* a_HealthComponent)> OnDeath;

public:
    HealthComponent(BadEngine::GameObject a_GameObject);

    void initialise(unsigned a_MaxHealth);
    void dealDamage(unsigned a_Amount);
    unsigned getCurrentHealth() const;
};

