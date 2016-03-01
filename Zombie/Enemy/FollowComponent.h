#pragma once
#include <Artifact/Core/Component.h>

class FollowComponent : public Artifact::Component
{
public:
    float FollowSpeed = 1.0f;
public:
    FollowComponent(Artifact::GameObject a_GameObject);
};