#include <Artifact/Physics/RigidBody2D.h>
#include <Artifact/Core/EntitySystem.h>

#include "FollowComponent.h"
#include "AttackComponent.h"
#include "ZombieBehaviour.h"

ZombieBehaviour::ZombieBehaviour(Artifact::GameObject a_GameObject)
    : Component(a_GameObject),
    m_AttackComponent(getComponent<AttackComponent>()),
    m_FollowComponent(getComponent<FollowComponent>())
{
    startFollowing();
}

void ZombieBehaviour::setState(EBehaviourstate a_NewState)
{
    if(a_NewState != m_State)
    {
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
    m_State = EBehaviourstate::Follow;
    m_FollowComponent->enable();
    m_AttackComponent->disable();
}

void ZombieBehaviour::startAttacking()
{
    m_State = EBehaviourstate::Attack;
    m_FollowComponent->disable();
    m_AttackComponent->enable();
    m_AttackComponent->startTimer();
    getComponent<Artifact::RigidBody2D>()->setVelocity(glm::vec2(0.0f, 0.0f));
}
