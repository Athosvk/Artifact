#pragma once
#include <Artifact/Core/World.h>

namespace Artifact
{
	class Game;
}

class PhysicsTestWorld : public Artifact::World
{
public:
    PhysicsTestWorld(Artifact::GameTime& a_GameTime, Artifact::Game* a_Game);
};

