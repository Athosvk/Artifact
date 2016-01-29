#include <BadEngine/Physics/BoxCollider2D.h>
#include <BadEngine/Physics/RigidBody.h>
#include <BadEngine/Core/EntitySystem.h>
#include <BadEngine/IO/ResourceManager.h>

#include "Box.h"

Box::Box(unsigned a_ID, BadEngine::EntitySystem& a_EntitySystem)
    : GameObject(a_ID, a_EntitySystem)
{
    m_Renderer = addComponent<BadEngine::SpriteRenderer>();
    m_Renderer->setTexture(BadEngine::ResourceManager::getTexture("Textures/Box.png"));

    m_Collider = addComponent<BadEngine::BoxCollider2D>();
    setDimensions(100, 100);
}

void Box::setDimensions(float a_Width, float a_Height)
{
    m_Renderer->Width = a_Width;
    m_Renderer->Height = a_Height;

    m_Collider->setWidth(a_Width);
    m_Collider->setHeight(a_Height);
}