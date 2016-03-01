#pragma once
#include <Artifact/Core/Component.h>
#include <Artifact/Delegate.h>

class HealthComponent : public Artifact::Component
{
private:
    unsigned m_CurrentHealth;
public:
    unsigned MaxHealth;
    Delegate<void(HealthComponent* a_HealthComponent)> OnDeath;

public:
    HealthComponent(Artifact::GameObject a_GameObject);

    void initialise(unsigned a_MaxHealth);
    void dealDamage(unsigned a_Amount);
    unsigned getCurrentHealth() const;
};

