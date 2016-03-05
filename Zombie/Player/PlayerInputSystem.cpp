#include <glm/glm.hpp>

#include <Artifact/Input/InputSystem.h>
#include <Artifact/Core/EntitySystem.h>
#include <Artifact/Physics/RigidBody2D.h>
#include <Artifact/Core/World.h>
#include <Artifact/MathHelper.h>

#include "PlayerInputSystem.h"
#include "PlayerInputComponent.h"
#include "WeaponSystem.h"

PlayerInputSystem::PlayerInputSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MessagingSystem)
    : System(a_EntitySystem, a_MessagingSystem)
{
}

void PlayerInputSystem::registerListeners()
{
    m_MessagingSystem.registerListener<Artifact::HandleInputMessage>([=](const Artifact::Message*)
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
    if(displacement != glm::vec2(0.0f, 0.0f))
    {
        glm::normalize(displacement);
        a_Player->getComponent<Artifact::Transform>()->
            setRotation(Artifact::MathHelper::directionToAngle(displacement));
    }
    a_Player->getComponent<Artifact::RigidBody2D>()->setVelocity(displacement * a_Player->MovementSpeed);
}

void PlayerInputSystem::updateFireState(PlayerInputComponent* a_Player)
{
    if(Artifact::Keyboard::isDown(a_Player->FireKey))
    {
        m_MessagingSystem.broadcast<FireWeaponMessage>(a_Player->Weapon);
    }
}