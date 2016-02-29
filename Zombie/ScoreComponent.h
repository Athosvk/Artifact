#pragma once
#include <BadEngine/Core/Component.h>

class ScoreComponent : public BadEngine::Component
{
public:
    int Amount = 1;

public:
    ScoreComponent(BadEngine::GameObject a_Entity);
};

