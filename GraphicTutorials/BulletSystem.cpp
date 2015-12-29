#include "BulletSystem.h"

BulletSystem::BulletSystem(BadEngine::EntitySystem& a_EntitySystem)
    : System(a_EntitySystem)
{
}

void BulletSystem::sendMessage(const BadEngine::Message* a_Message)
{
    switch(a_Message->getType())
    {
    case BadEngine::EMessageType::Update:
        update();
    default:
        break;
    }
}

void BulletSystem::update()
{

}