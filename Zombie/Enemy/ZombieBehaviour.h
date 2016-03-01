#pragma once
#include <Artifact/Core/Component.h>

class FollowComponent;
class AttackComponent;

enum class EBehaviourstate
{
    Follow,
    Attack
};

class ZombieBehaviour : public Artifact::Component
{
private:
    EBehaviourstate m_State;
    FollowComponent* m_FollowComponent;
    AttackComponent* m_AttackComponent;
public:
    float AttackRadius = 0.7f;

public:
    ZombieBehaviour(Artifact::GameObject a_GameObject);

    void setState(EBehaviourstate a_NewState);
private:
    void startFollowing();
    void startAttacking();
};

