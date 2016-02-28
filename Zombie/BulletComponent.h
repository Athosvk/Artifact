#pragma once
#include <BadEngine/Core/Component.h>

#include "TagComponent.h"

class BulletComponent : public BadEngine::Component
{
public:
    float Speed = 1.0f;
    int Damage = 1;
    EType BlockingTag;
    EType TargetTag = EType::Enemy;

public:
    BulletComponent(BadEngine::GameObject a_GameObject);
};

