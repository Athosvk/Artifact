#pragma once
#include <BadEngine/Transform.h>

class CharacterController
{
private:
    BadEngine::Transform& m_PlayerTransform;
    float m_Speed = 2.5f;

public:
    CharacterController(BadEngine::Transform& a_PlayerTransform);
    ~CharacterController();

    void fixedUpdate() const;
};

