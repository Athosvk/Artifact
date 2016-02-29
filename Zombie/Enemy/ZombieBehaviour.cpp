#include <BadEngine/Physics/RigidBody2D.h>
#include <BadEngine/Core/EntitySystem.h>

#include "ZombieBehaviour.h"

ZombieBehaviour::ZombieBehaviour(BadEngine::GameObject a_GameObject)
    : Component(a_GameObject)
{
}

void ZombieBehaviour::setState(EBehaviourstate a_NewState)
{
    m_State = a_NewState;
    switch(a_NewState)
    {
    case EBehaviourstate::Follow:
        startFollowing();
        break;
    case EBehaviourstate::Attack:
        startAttacking();
        break;
    }
}

void ZombieBehaviour::startFollowing()
{
    FollowComponent->enable();
    AttackComponent->disable();
}

void ZombieBehaviour::startAttacking()
{
    FollowComponent->disable();
    AttackComponent->enable();
    getComponent<BadEngine::RigidBody2D>()->setVelocity(glm::vec2(0.0f, 0.0f));
}
