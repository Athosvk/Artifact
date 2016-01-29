#pragma once
#include <BadEngine/Core/GameObject.h>

class Bullet : public BadEngine::GameObject
{
public:
    Bullet(unsigned a_ID, BadEngine::EntitySystem& a_EntitySystem);
};

