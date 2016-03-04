#pragma once
#include <Artifact/EnumUtility.h>

enum class ECollisionLayer : uint16
{
    None = 0,
    Player = 2,
    Enemy = 4,
    Wall = 8,
    Bullet = 16,
    All = 31
};
EnumFlagOperators(ECollisionLayer);