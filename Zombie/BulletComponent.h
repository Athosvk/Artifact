#pragma once
#include <Artifact/Core/Component.h>

#include "TagComponent.h"

class BulletComponent : public Artifact::Component
{
public:
    float Speed = 1.0f;
    int Damage = 1;
    EType BlockingTag = EType::Wall;
    EType TargetTag = EType::Enemy;

public:
    BulletComponent(Artifact::GameObject a_GameObject);
};

