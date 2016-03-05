#pragma once
#include <Artifact/Core/GameObject.h>
#include <Artifact/Rendering/SpriteRenderer.h>

class Player : Artifact::GameObject
{
public:
    Player(unsigned a_ID, Artifact::EntitySystem& a_EntitySystem);
};

