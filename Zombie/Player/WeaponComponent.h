#pragma once
#include <Artifact/Core/Component.h>
#include <Artifact/Transform.h>

#include "../TimerComponent.h"

class WeaponComponent : public Artifact::Component
{
public:
    Artifact::Transform* MuzzleTransform;
    TimerComponent* FireDelayTimer;

public:
    WeaponComponent(Artifact::GameObject a_GameObject);
};

