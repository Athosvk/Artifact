#pragma once
#include <BadEngine/Core/Component.h>

class PlayerScoreComponent : public BadEngine::Component
{
public:
    unsigned CurrentScore = 0;

public:
    PlayerScoreComponent(BadEngine::GameObject a_Entity);
};

