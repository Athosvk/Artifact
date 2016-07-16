#include <Box2D/Box2D.h>

#include "BoxCollider2D.h"
#include "../Rendering/SpriteRenderer.h"
#include "../Transform.h"
#include "../Core/EntitySystem.h"

namespace Artifact
{
    BoxCollider2D::BoxCollider2D(GameObject a_GameObject)
        : Component(a_GameObject),
		m_GameObjectHandle(std::make_shared<GameObject>(getGameObject()))
    {
        m_FixtureDefinition.density = 1.0f;
		m_FixtureDefinition.userData = m_GameObjectHandle.get();
    }

    BoxCollider2D::~BoxCollider2D()
    {
        //m_Body->DestroyFixture(m_Fixture);
    }

    glm::vec2 BoxCollider2D::getDimensions() const
    {
        return m_Dimensions;
    }

    void BoxCollider2D::setDimensions(glm::vec2 a_Dimensions)
    {
        m_Shape.SetAsBox(a_Dimensions.x / 2, a_Dimensions.y / 2);
        m_ShapeDirty = true;
        m_Dimensions = a_Dimensions;
    }

    bool BoxCollider2D::isTrigger() const
    {
        return m_FixtureDefinition.isSensor;
    }

    void BoxCollider2D::enableTriggerState()
    {
        m_FixtureDefinition.isSensor = true;
    }

    void BoxCollider2D::disableTriggerState()
    {
        m_FixtureDefinition.isSensor = false;
    }

    uint16 BoxCollider2D::getLayer() const
    {
        return m_FixtureDefinition.filter.categoryBits;
    }

    void BoxCollider2D::setLayer(uint16 a_Layer)
    {
        m_FixtureDefinition.filter.categoryBits = a_Layer;
    }

    uint16 BoxCollider2D::getMask() const
    {
        return m_FixtureDefinition.filter.maskBits;
    }

    void BoxCollider2D::setMask(uint16 a_Mask)
    {
        m_FixtureDefinition.filter.maskBits = a_Mask;
    }

    void BoxCollider2D::attachFixture()
    {
        if(m_Fixture != nullptr)
        {
            m_Body->DestroyFixture(m_Fixture);
        }
        m_FixtureDefinition.shape = &m_Shape;
        m_Fixture = m_Body->CreateFixture(&m_FixtureDefinition);
        m_ShapeDirty = false;
    }

    void BoxCollider2D::refreshFixtureData() const
    {
        m_Fixture->SetSensor(m_FixtureDefinition.isSensor);
    }

    void BoxCollider2D::onPrePhysicsUpdate()
    {
        if(m_ShapeDirty)
        {
            attachFixture();
        }
        else
        {
            refreshFixtureData();
        }
        auto transform = getComponent<Transform>();
        m_Body->SetTransform(b2Vec2(transform->getPosition().x, transform->getPosition().y), 
			glm::radians(transform->getRotation()));
    }
}
