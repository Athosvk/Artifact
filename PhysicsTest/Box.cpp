#include <Artifact/Physics/BoxCollider2D.h>
#include <Artifact/Physics/RigidBody2D.h>
#include <Artifact/Core/EntitySystem.h>
#include <Artifact/IO/ResourceManager.h>
#include <Artifact/Transform.h>

#include "Box.h"

Box::Box(unsigned a_ID, Artifact::EntitySystem& a_EntitySystem)
    : GameObject(a_ID, a_EntitySystem)
{
    m_Renderer = addComponent<Artifact::SpriteRenderer>();
    m_Renderer->setTexture(Artifact::ResourceManager::getTexture("Textures/Box.png"));

    //m_Collider = addComponent<Artifact::BoxCollider2D>();
    setDimensions(0.2f, 0.2f);
}

void Box::setDimensions(float a_Width, float a_Height)
{
    m_Renderer->Width = a_Width;
    m_Renderer->Height = a_Height;

    //m_Collider->setDimensions(glm::vec2(a_Width, a_Height));
}
