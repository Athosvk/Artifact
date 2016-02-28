#pragma once
#include <BadEngine/EnumUtility.h>
#include <BadEngine/Core/Component.h>

enum class EType
{
    Player = 1,
    Enemy = 2,
    All = 4
};
EnumFlagOperators(EType)

class DamageComponent : public BadEngine::Component
{
public:
    int Damage = 1;
    EType TargetType = EType::All;

public:
    DamageComponent(BadEngine::GameObject a_GameObject);
};
