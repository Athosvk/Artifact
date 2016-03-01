#pragma once
#include <Artifact/Core/GameObject.h>

class Spawner : public Artifact::GameObject
{
public:
    Spawner(unsigned a_ID, Artifact::EntitySystem& a_EntitySystem);
};

