#pragma once
#include <BadEngine/Core/Component.h>
#include <BadEngine/Transform.h>

class WeaponComponent : public BadEngine::Component
{
public:
    int ClipSize;
    int BulletsLeft;
    BadEngine::Transform* MuzzleTransform;

public:
    WeaponComponent(BadEngine::GameObject a_GameObject);

    void reload();
};

