#include "CollisionMessages.h"

namespace Artifact
{
    Collision2DMessage::Collision2DMessage(BoxCollider2D* a_Collider, BoxCollider2D* a_Other)
        : m_Collider(a_Collider), m_Other(a_Other)
    {
    }

    BoxCollider2D* Collision2DMessage::getCollider() const
    {
        return m_Collider;
    }

    BoxCollider2D* Collision2DMessage::getOther() const
    {
        return m_Other;
    }

    CollisionEnter2DMessage::CollisionEnter2DMessage(BoxCollider2D* a_Collider, BoxCollider2D* a_Other)
        : Collision2DMessage(a_Collider, a_Other)
    {
    }

    TriggerEnter2DMessage::TriggerEnter2DMessage(BoxCollider2D* a_Collider, BoxCollider2D* a_Other)
        : Collision2DMessage(a_Collider, a_Other)
    {
    }

    CollisionExit2DMessage::CollisionExit2DMessage(BoxCollider2D* a_Collider, BoxCollider2D* a_Other)
        : Collision2DMessage(a_Collider, a_Other)
    {
    }

    TriggerExit2DMessage::TriggerExit2DMessage(BoxCollider2D* a_Collider, BoxCollider2D* a_Other)
        : Collision2DMessage(a_Collider, a_Other)
    {
    }
}