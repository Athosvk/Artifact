#pragma once
#include "../Transform.h"

class CharacterController
{
private:
    Transform& m_PlayerTransform;
    float m_Speed = 2.5f;

public:
    CharacterController(Transform& a_PlayerTransform);
    ~CharacterController();

    void fixedUpdate() const;
};

