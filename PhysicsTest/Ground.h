#pragma once
#include <Artifact/Core/GameObject.h>

class Ground : public Artifact::GameObject
{
public:
    Ground(unsigned a_ID, Artifact::EntitySystem& a_EntitySystem);
};

