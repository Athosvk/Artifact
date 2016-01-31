#include <glm/glm.hpp>

#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/Physics/RigidBody2D.h>
#include <BadEngine/Input/InputSystem.h>

#include "PlayerInputSystem.h"
#include "PlayerInputComponent.h"

PlayerInputSystem::PlayerInputSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem)
{
}

void PlayerInputSystem::registerListeners()
{
    m_MessagingSystem.registerListener<BadEngine::HandleInputMessage>([=](const BadEngine::Message* a_Message)
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

void PlayerInputSystem::updatePlayerMovement(PlayerInputComponent* a_Player)
{
    glm::vec2 displacement = glm::vec2(0, 0);
    if(BadEngine::Keyboard::isDown(a_Player->MoveUpKey))
    {
        displacement.y++;
    }
    if(BadEngine::Keyboard::isDown(a_Player->MoveDownKey))
    {
        displacement.y--;
    }
    if(BadEngine::Keyboard::isDown(a_Player->MoveLeftKey))
    {
        displacement.x--;
    }
    if(BadEngine::Keyboard::isDown(a_Player->MoveRightKey))
    {
        displacement.x++;
    }
    auto rigidBody = a_Player->getComponent<BadEngine::RigidBody2D>();
    if(displacement != glm::vec2(0, 0))
    {
        rigidBody->setVelocity(glm::vec2((glm::normalize(displacement) * 0.75f).x, rigidBody->getVelocity().y));
    }
}