#include <BadEngine/Core/World.h>
#include <BadEngine/Physics/RigidBody2D.h>
#include <BadEngine/Transform.h>
#include <BadEngine/MathHelper.h>

#include "FollowSystem.h"
#include "FollowComponent.h"
#include "../Player/PlayerComponent.h"

FollowSystem::FollowSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem)
{
}

void FollowSystem::registerListeners()
{
    m_MessagingSystem.registerListener<BadEngine::UpdateMessage>([this](const BadEngine::Message*)
    {
        updateVelocities();
    });
}

void FollowSystem::updateVelocities()
{
    auto playerPosition = getCurrentPlayer()->getComponent<BadEngine::Transform>()->getPosition();

    for(auto follower : m_EntitySystem.getComponentsOfType<FollowComponent>())
    {
        auto followerTransform = follower->getComponent<BadEngine::Transform>();
        if (followerTransform->getPosition() != playerPosition)
        {
            auto newDirection = glm::normalize(playerPosition - followerTransform->getPosition());
            follower->getComponent<BadEngine::RigidBody2D>()->setVelocity(newDirection * follower->FollowSpeed);
            followerTransform->setRotation(BadEngine::MathHelper::directionToAngle(newDirection));
        }
    }
}

PlayerComponent * FollowSystem::getCurrentPlayer()
{
    return m_EntitySystem.getComponentsOfType<PlayerComponent>()[0];
}
