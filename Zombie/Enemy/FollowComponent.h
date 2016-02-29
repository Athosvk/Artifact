#pragma once
#include <BadEngine/Core/Component.h>

class FollowComponent : public BadEngine::Component
{
public:
    float FollowSpeed = 1.0f;
public:
    FollowComponent(BadEngine::GameObject a_GameObject);
};