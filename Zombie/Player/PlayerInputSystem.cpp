#include <glm/glm.hpp>

#include <BadEngine/Input/InputSystem.h>
#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/Physics/RigidBody2D.h>
#include <BadEngine/Core/World.h>
#include <BadEngine/MathHelper.h>

#include "PlayerInputSystem.h"
#include "PlayerInputComponent.h"
#include "WeaponSystem.h"

PlayerInputSystem::PlayerInputSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem)
{
}

void PlayerInputSystem::registerListeners()
{
    m_MessagingSystem.registerListener<BadEngine::HandleInputMessage>([=](const BadEngine::Message*)
    {
        handleInput();
    });
}

void PlayerInputSystem::handleInput()
{
    for(auto player : m_EntitySystem.getComponentsOfType<PlayerInputComponent>())
    {
        updatePlayerMovement(player);
        updateFireState(player);
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
    if(displacement != glm::vec2(0.0f, 0.0f))
    {
        glm::normalize(displacement);
        a_Player->getComponent<BadEngine::Transform>()->setRotation(BadEngine::MathHelper::directionToAngle(displacement));
    }
    a_Player->getComponent<BadEngine::RigidBody2D>()->setVelocity(displacement * a_Player->MovementSpeed);
}

void PlayerInputSystem::updateFireState(PlayerInputComponent* a_Player)
{
    if(BadEngine::Keyboard::isDown(a_Player->FireKey))
    {
        m_MessagingSystem.broadcast<FireWeaponMessage>(a_Player->Weapon);
    }
}