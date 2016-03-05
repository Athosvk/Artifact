#pragma once
#include <Artifact/Core/Component.h>

class ScoreComponent : public Artifact::Component
{
public:
    int Amount = 1;

public:
    ScoreComponent(Artifact::GameObject a_Entity);
};

