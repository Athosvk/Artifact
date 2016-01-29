#pragma once
#include <BadEngine/Core/Component.h>
#include <BadEngine/Transform.h>

#include "../TimerComponent.h"

class WeaponComponent : public BadEngine::Component
{
public:
    BadEngine::Transform* MuzzleTransform;
    TimerComponent* FireDelayTimer;

public:
    WeaponComponent(BadEngine::GameObject a_GameObject);
};

