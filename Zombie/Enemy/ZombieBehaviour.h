#pragma once
#include <BadEngine/Core/Component.h>

class FollowComponent;
class AttackComponent;

enum class EBehaviourstate
{
    Follow,
    Attack
};

class ZombieBehaviour : public BadEngine::Component
{
private:
    EBehaviourstate m_State;
public:
    FollowComponent* FollowComponent;
    AttackComponent* AttackComponent;
    float AttackRadius = 1.0f;

public:
    ZombieBehaviour(BadEngine::GameObject a_GameObject);

    void setState(EBehaviourstate a_NewState);
private:
    void startFollowing();
    void startAttacking();
};

