#pragma once
#include <Artifact/Core/Component.h>

class PlayerScoreComponent : public Artifact::Component
{
public:
    unsigned CurrentScore = 0;

public:
    PlayerScoreComponent(Artifact::GameObject a_Entity);
};

