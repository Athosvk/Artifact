#pragma once
#include <string>

#include <Artifact/EnumUtility.h>
#include <Artifact/Core/Component.h>

enum class EType
{
    Player = 1,
    Enemy = 2,
    Wall = 4,
    All = Enemy | Player | Wall
};
EnumFlagOperators(EType)

class TagComponent : public Artifact::Component
{
public:
    EType Type;
    std::string Name;

public:
    TagComponent(Artifact::GameObject a_GameObject);
};

