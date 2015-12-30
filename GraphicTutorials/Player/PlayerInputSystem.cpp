#include <glm/glm.hpp>

#include <BadEngine/Input/Keyboard.h>
#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/Physics/MovementComponent.h>

#include "PlayerInputSystem.h"
#include "PlayerInputComponent.h"

PlayerInputSystem::PlayerInputSystem(BadEngine::EntitySystem& a_EntitySystem)
    : System(a_EntitySystem)
{
}

void PlayerInputSystem::sendMessage(const BadEngine::Message* a_Message)
{
    switch(a_Message->getType())
    {
    case BadEngine::EMessageType::HandleInput:
        handleInput();
    default:
        break;
    }
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
    a_Player->getComponent<BadEngine::MovementComponent>()->Direction = displacement;
}

void PlayerInputSystem::updateFireState(PlayerInputComponent* a_Player)
{
    if(BadEngine::Keyboard::isDown(a_Player->FireKey))
    {
        
    }
}