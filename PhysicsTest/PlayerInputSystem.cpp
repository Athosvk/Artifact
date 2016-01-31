#include <glm/glm.hpp>
#include <iostream>

#include <BadEngine/Input/Keyboard.h>
#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/Physics/RigidBody2D.h>
#include <BadEngine/Core/World.h>
#include <BadEngine/Physics/CollisionMessages.h>

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
    m_MessagingSystem.registerListener<BadEngine::CollisionExit2DMessage>([=](const BadEngine::Message* a_Message)
    {
        auto message = static_cast<const BadEngine::CollisionExit2DMessage*>(a_Message);
        onCollisionEnter(message->getCollider(), message->getOther());
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
        //displacement.y++;
    }
    if(BadEngine::Keyboard::isDown(a_Player->MoveDownKey))
    {
        //displacement.y--;
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

void PlayerInputSystem::onCollisionEnter(BadEngine::BoxCollider2D* a_Collider, BadEngine::BoxCollider2D* a_Other)
{
   // std::cout << "YAY " << a_Collider->getGameObject().getID() << ", " << a_Other->getGameObject().getID() << "\n";
}