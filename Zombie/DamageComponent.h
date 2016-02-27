#pragma once
#include <BadEngine/Core/Component.h>

class DamageComponent : public BadEngine::Component
{
public:
    int Damage = 1;
public:
    DamageComponent(BadEngine::GameObject a_GameObject);
};

