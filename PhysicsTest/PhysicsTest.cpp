#include "PhysicsTest.h"
#include "PhysicsTestWorld.h"

PhysicsTest::PhysicsTest()
    : Game(1024, 768, BadEngine::WindowFlag::Borderless, "Physics Test")
{
    loadWorld<PhysicsTestWorld>();
}

PhysicsTest::~PhysicsTest()
{

}
