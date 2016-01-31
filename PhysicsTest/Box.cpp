#include <BadEngine/Physics/BoxCollider2D.h>
#include <BadEngine/Physics/RigidBody2D.h>
#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/IO/ResourceManager.h>
#include <BadEngine/Transform.h>

#include "Box.h"

Box::Box(unsigned a_ID, BadEngine::EntitySystem& a_EntitySystem)
    : GameObject(a_ID, a_EntitySystem)
{
    m_Renderer = addComponent<BadEngine::SpriteRenderer>();
    m_Renderer->setTexture(BadEngine::ResourceManager::getTexture("Textures/Box.png"));

    //m_Collider = addComponent<BadEngine::BoxCollider2D>();
    setDimensions(0.2f, 0.2f);
}

void Box::setDimensions(float a_Width, float a_Height)
{
    m_Renderer->Width = a_Width;
    m_Renderer->Height = a_Height;

    //m_Collider->setDimensions(glm::vec2(a_Width, a_Height));
}
