#include "CollisionMessages.h"

namespace BadEngine
{
    CollisionEnter2DMessage::CollisionEnter2DMessage(BoxCollider2D* a_Collider, BoxCollider2D* a_Other)
        : m_Collider(a_Collider), m_Other(a_Other)
    {
    }

    BoxCollider2D* CollisionEnter2DMessage::getCollider() const
    {
        return m_Collider;
    }

    BoxCollider2D* CollisionEnter2DMessage::getOther() const
    {
        return m_Other;
    }
}