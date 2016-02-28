#pragma once
#include <BadEngine/Core/Component.h>

#include "DamageComponent.h"

class HealthComponent : public BadEngine::Component
{
public:
    EType ObjectType;
    unsigned CurrentHealth;
    unsigned MaxHealth;

public:
    HealthComponent(BadEngine::GameObject a_GameObject);
};

