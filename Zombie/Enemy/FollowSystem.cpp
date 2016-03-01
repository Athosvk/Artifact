#include <Artifact/Core/World.h>
#include <Artifact/Physics/RigidBody2D.h>
#include <Artifact/Transform.h>
#include <Artifact/MathHelper.h>

#include "FollowSystem.h"
#include "FollowComponent.h"
#include "../Player/PlayerComponent.h"

FollowSystem::FollowSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem)
{
}

void FollowSystem::registerListeners()
{
    m_MessagingSystem.registerListener<Artifact::UpdateMessage>([this](const Artifact::Message*)
    {
        updateVelocities();
    });
}

void FollowSystem::updateVelocities()
{
    auto playerPosition = getCurrentPlayer()->getComponent<Artifact::Transform>()->getPosition();

    for(auto follower : m_EntitySystem.getComponentsOfType<FollowComponent>())
    {
        auto followerTransform = follower->getComponent<Artifact::Transform>();
        if (followerTransform->getPosition() != playerPosition)
        {
            auto newDirection = glm::normalize(playerPosition - followerTransform->getPosition());
            follower->getComponent<Artifact::RigidBody2D>()->setVelocity(newDirection * follower->FollowSpeed);
            followerTransform->setRotation(Artifact::MathHelper::directionToAngle(newDirection));
        }
    }
}

PlayerComponent* FollowSystem::getCurrentPlayer()
{
    return m_EntitySystem.getComponentsOfType<PlayerComponent>()[0];
}
