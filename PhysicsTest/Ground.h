#pragma once
#include <BadEngine/Core/GameObject.h>

class Ground : public BadEngine::GameObject
{
public:
    Ground(unsigned a_ID, BadEngine::EntitySystem& a_EntitySystem);
};

