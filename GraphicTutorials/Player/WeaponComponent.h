#pragma once
#include <BadEngine/Core/Component.h>
#include <BadEngine/Transform.h>

class WeaponComponent : BadEngine::Component
{
public:
    int m_ClipSize;
    int m_BulletsLeft;
    BadEngine::Transform* m_MuzzleTransform;

public:
    WeaponComponent(BadEngine::GameObject a_GameObject);

    void reload();
};

