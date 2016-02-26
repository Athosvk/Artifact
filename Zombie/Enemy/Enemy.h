#pragma once
#include <BadEngine/Core/GameObject.h>

class Enemy : public BadEngine::GameObject
{
public:
    Enemy(unsigned a_ID, BadEngine::EntitySystem& a_EntitySystem);
};

