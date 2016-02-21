#pragma once
#include <BadEngine/Core/Component.h>

class HealthComponent : public BadEngine::Component
{
public:
    unsigned CurrentHealth;
    unsigned MaxHealth;

public:
    HealthComponent(BadEngine::GameObject a_GameObject);
};

