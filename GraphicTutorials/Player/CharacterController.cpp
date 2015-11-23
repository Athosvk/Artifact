#include <BadEngine/Input/Keyboard.h>
#include <glm/glm.hpp>

#include "CharacterController.h"

CharacterController::CharacterController(Transform& a_PlayerTransform)
    : m_PlayerTransform(a_PlayerTransform)
{
}

CharacterController::~CharacterController()
{
}

void CharacterController::fixedUpdate() const
{
    glm::vec2 displacement = glm::vec2(0, 0);
    if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::W))
    {
        displacement.y += 1.0f;
    }
    if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::S))
    {
        displacement.y -= 1.0f;
    }
    if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::A))
    {
        displacement.x -= 1.0f;
    }
    if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::D))
    {
        displacement.x += 1.0f;
    }
    if(displacement != glm::vec2(0.0f, 0.0f))
    {
        m_PlayerTransform.translate(glm::normalize(displacement) * m_Speed);
    }
}
