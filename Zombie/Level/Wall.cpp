#include <Artifact/Core/EntitySystem.h>
#include <Artifact/Physics/BoxCollider2D.h>
#include <Artifact/Rendering/SpriteRenderer.h>
#include <Artifact/Transform.h>

#include "Wall.h"
#include "../TagComponent.h"
#include "../CollisionLayers.h"

Wall::Wall(Artifact::EntitySystem& a_EntitySystem, Artifact::GLTexture* a_Texture, glm::vec2 a_Dimensions)
    : m_Entity(a_EntitySystem.createEntity())
{
    if(a_Texture != nullptr)
    {
        auto renderer = m_Entity.addComponent<Artifact::SpriteRenderer>();
        renderer->setTexture(a_Texture);
        renderer->Width = a_Dimensions.x;
        renderer->Height = a_Dimensions.y;
        renderer->Depth = 10;
    }
    auto collider = m_Entity.addComponent<Artifact::BoxCollider2D>();
    collider->setDimensions(a_Dimensions);
    collider->setLayer(static_cast<uint16>(ECollisionLayer::Wall));
    collider->setMask(static_cast<uint16>(ECollisionLayer::Player | ECollisionLayer::Bullet));

    auto tag = m_Entity.addComponent<TagComponent>();
    tag->Type = EType::Wall;
}

void Wall::setPosition(glm::vec2 a_Position)
{
    m_Entity.getComponent<Artifact::Transform>()->setPosition(a_Position);
}