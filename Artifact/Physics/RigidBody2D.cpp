#include "RigidBody2D.h"
#include "BoxCollider2D.h"
#include "../Transform.h"

namespace Artifact
{
    RigidBody2D::RigidBody2D(GameObject a_GameObject)
        : Component(a_GameObject)
    {
    }

    void RigidBody2D::setVelocity(glm::vec2 a_Velocity) const
    {
        m_Body->SetLinearVelocity(b2Vec2(a_Velocity.x, a_Velocity.y));
    }

    glm::vec2 RigidBody2D::getVelocity() const
    {
        return glm::vec2(m_Body->GetLinearVelocity().x, m_Body->GetLinearVelocity().y);
    }

    void RigidBody2D::setGravityScale(float a_Scale) const
    {
        m_Body->SetGravityScale(a_Scale);
    }

    void RigidBody2D::makeKinematic() const
    {
        m_Body->SetType(b2BodyType::b2_kinematicBody);
    }

    void RigidBody2D::makeDynamic() const
    {
        m_Body->SetType(b2BodyType::b2_dynamicBody);
    }

    bool RigidBody2D::isKinematic() const
    {
        return m_Body->GetType() == b2BodyType::b2_kinematicBody;
    }
     
    void RigidBody2D::updateState() const
    {
        auto transform = getComponent<Transform>();
        transform->setPosition(glm::vec2(m_Body->GetPosition().x, m_Body->GetPosition().y));
        transform->setRotation(glm::degrees(m_Body->GetAngle()));
    }
}