#pragma once
#include <BadEngine/Core/Component.h>

#include "../TimerComponent.h"

class AttackComponent : public BadEngine::Component
{
public:
    float AttackInterval = 1.0f;
    TimerComponent* DelayTimer;
    int Damage = 1;

public:
    AttackComponent(BadEngine::GameObject a_GameObject);
};

