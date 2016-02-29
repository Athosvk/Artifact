#pragma once
#include <string>

#include <BadEngine/EnumUtility.h>
#include <BadEngine/Core/Component.h>

enum class EType
{
    Player = 1,
    Enemy = 2,
    All = Enemy | Player
};
EnumFlagOperators(EType)

class TagComponent : public BadEngine::Component
{
public:
    EType Type;
    std::string Name;

public:
    TagComponent(BadEngine::GameObject a_GameObject);
};

