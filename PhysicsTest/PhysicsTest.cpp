#include "PhysicsTest.h"
#include "PhysicsTestWorld.h"

PhysicsTest::PhysicsTest()
    : Game(1024, 768, 0, "Physics Test")
{
    loadWorld<PhysicsTestWorld>();
}

PhysicsTest::~PhysicsTest()
{

}
