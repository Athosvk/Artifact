#pragma once
#include <Artifact/Core/GameObject.h>

class Bullet : public Artifact::GameObject
{
public:
    Bullet(unsigned a_ID, Artifact::EntitySystem& a_EntitySystem);
};

