#pragma once
#include <Artifact/Core/GameObject.h>

class Enemy : public Artifact::GameObject
{
public:
    Enemy(unsigned a_ID, Artifact::EntitySystem& a_EntitySystem);
};

