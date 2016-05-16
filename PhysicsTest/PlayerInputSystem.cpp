#include <glm/glm.hpp>

#include <Artifact/Core/EntitySystem.h>
#include <Artifact/Physics/RigidBody2D.h>
#include <Artifact/Input/InputSystem.h>

#include "PlayerInputSystem.h"
#include "PlayerInputComponent.h"

PlayerInputSystem::PlayerInputSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem)
{
}

void PlayerInputSystem::registerListeners()
{
    m_MessagingSystem.registerListener<Artifact::HandleInputMessage>([=](const Artifact::Message* a_Message)
    {
        handleInput();
    });
}

void PlayerInputSystem::handleInput()
{
    for(auto player : m_EntitySystem.getComponentsOfType<PlayerInputComponent>())
    {
        updatePlayerMovement(player);
    }
}

void PlayerInputSystem::updatePlayerMovement(Artifact::ComponentHandle<PlayerInputComponent> a_Player)
{
    glm::vec2 displacement = glm::vec2(0, 0);
    if(Artifact::Keyboard::isDown(a_Player->MoveUpKey))
    {
        displacement.y++;
    }
    if(Artifact::Keyboard::isDown(a_Player->MoveDownKey))
    {
        displacement.y--;
    }
    if(Artifact::Keyboard::isDown(a_Player->MoveLeftKey))
    {
        displacement.x--;
    }
    if(Artifact::Keyboard::isDown(a_Player->MoveRightKey))
    {
        displacement.x++;
    }
    auto rigidBody = a_Player->getComponent<Artifact::RigidBody2D>();
    if(displacement != glm::vec2(0, 0))
    {
        rigidBody->setVelocity(glm::vec2((glm::normalize(displacement) * 0.75f).x, rigidBody->getVelocity().y));
    }
}