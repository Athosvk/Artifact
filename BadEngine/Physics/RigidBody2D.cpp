#include "RigidBody2D.h"
#include "BoxCollider2D.h"
#include "../Transform.h"

namespace BadEngine
{
    RigidBody2D::RigidBody2D(GameObject a_GameObject)
        : Component(a_GameObject)
    {
    }

    void RigidBody2D::setVelocity(glm::vec2 a_Velocity)
    {
        if(m_Body)
        {
           m_Body->SetLinearVelocity(b2Vec2(a_Velocity.x, a_Velocity.y));
        }
    }

    glm::vec2 RigidBody2D::getVelocity() const
    {
        if(m_Body)
        {
            return glm::vec2(m_Body->GetLinearVelocity().x, m_Body->GetLinearVelocity().y);
        }
        return glm::vec2(0, 0);
    }
     
    void RigidBody2D::updateState()
    {
        auto transform = getComponent<Transform>();
        transform->setPosition(glm::vec2(m_Body->GetPosition().x, m_Body->GetPosition().y));
        transform->setRotation(m_Body->GetAngle());
    }
}