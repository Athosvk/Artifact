#include <Box2D\Box2D.h>

#include "BoxCollider2D.h"
#include "../Rendering/SpriteRenderer.h"
#include "../Transform.h"
#include "../Core/EntitySystem.h"

namespace BadEngine
{
    BoxCollider2D::BoxCollider2D(GameObject a_GameObject)
        : Component(a_GameObject)
    {
    }

    BoxCollider2D::~BoxCollider2D()
    {
        m_Body->DestroyFixture(m_Fixture);
    }

    glm::vec2 BoxCollider2D::getDimensions() const
    {
        return m_Dimensions;
    }

    void BoxCollider2D::setDimensions(glm::vec2 a_Dimensions)
    {
        m_ShapeDirty = true;
        m_Dimensions = a_Dimensions;
    }

    void BoxCollider2D::createFixture()
    {
        if(m_Fixture != nullptr)
        {
            m_Body->DestroyFixture(m_Fixture);
        }
        m_Shape.SetAsBox(m_Dimensions.x / 2, m_Dimensions.y / 2);

        b2FixtureDef fixtureDefinition;
        fixtureDefinition.userData = this;
        //Density is only for standard functionality
        fixtureDefinition.density = 1.0f;
        fixtureDefinition.shape = &m_Shape;
        m_Fixture = m_Body->CreateFixture(&fixtureDefinition);
        m_ShapeDirty = false;
    }

    void BoxCollider2D::onPrePhysicsUpdate()
    {
        if(m_ShapeDirty)
        {
            createFixture();
        }
        auto transform = getComponent<Transform>();
        m_Body->SetTransform(b2Vec2(transform->getPosition().x, transform->getPosition().y), transform->getRotation());
    }
}
