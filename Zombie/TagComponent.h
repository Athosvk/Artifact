#pragma once
#include <string>

#include <Artifact/EnumUtility.h>
#include <Artifact/Core/Component.h>

enum class EType
{
    Player = 1,
    Enemy = 2,
    All = Enemy | Player
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

