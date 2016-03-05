#pragma once
#include <Artifact/Core/Component.h>
#include <Artifact/Delegate.h>

class HealthComponent : public Artifact::Component
{
private:
    unsigned m_CurrentHealth;
public:
    
    unsigned MaxHealth;
    Artifact::Delegate<void(HealthComponent* a_HealthComponent)> OnDeath;
    Artifact::Delegate<void()> OnHit;

public:
    HealthComponent(Artifact::GameObject a_GameObject);

    void initialise(unsigned a_MaxHealth);
    void dealDamage(unsigned a_Amount);
    unsigned getCurrentHealth() const;
};

