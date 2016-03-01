#pragma once
#include <Artifact/Core/GameObject.h>

class Player : public Artifact::GameObject
{
public:
    Player(unsigned a_ID, Artifact::EntitySystem& a_EntitySystem);
};

