#include <Artifact/Physics/RigidBody2D.h>
#include <Artifact/Core/EntitySystem.h>

#include "FollowComponent.h"
#include "AttackComponent.h"
#include "ZombieBehaviour.h"

ZombieBehaviour::ZombieBehaviour(Artifact::GameObject a_GameObject)
    : Component(a_GameObject)
{
}

void ZombieBehaviour::setState(EBehaviourstate a_NewState)
{
    if(a_NewState != m_State)
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
    AttackComponent->startTimer();
    getComponent<Artifact::RigidBody2D>()->setVelocity(glm::vec2(0.0f, 0.0f));
}
