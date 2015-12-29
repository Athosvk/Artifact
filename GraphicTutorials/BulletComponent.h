#pragma once
#include <glm/glm.hpp>

#include <BadEngine/Core/Component.h>

class BulletComponent : public BadEngine::Component
{
public:
    glm::vec2 StartPosition;
    float Speed = 5.0f;
    float LifeTime = 1.0f;

public:
    BulletComponent(BadEngine::GameObject a_GameObject);
};

