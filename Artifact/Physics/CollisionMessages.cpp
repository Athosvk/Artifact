#include "CollisionMessages.h"

namespace Artifact
{
    Collision2DMessage::Collision2DMessage(ComponentHandle<BoxCollider2D> a_Collider, ComponentHandle<BoxCollider2D> a_Other)
        : m_Collider(a_Collider), m_Other(a_Other)
    {
    }

    ComponentHandle<BoxCollider2D> Collision2DMessage::getCollider() const
    {
        return m_Collider;
    }

    ComponentHandle<BoxCollider2D> Collision2DMessage::getOther() const
    {
        return m_Other;
    }

    CollisionEnter2DMessage::CollisionEnter2DMessage(ComponentHandle<BoxCollider2D> a_Collider, ComponentHandle<BoxCollider2D> a_Other)
        : Collision2DMessage(a_Collider, a_Other)
    {
    }

    TriggerEnter2DMessage::TriggerEnter2DMessage(ComponentHandle<BoxCollider2D> a_Collider, ComponentHandle<BoxCollider2D> a_Other)
        : Collision2DMessage(a_Collider, a_Other)
    {
    }

    CollisionExit2DMessage::CollisionExit2DMessage(ComponentHandle<BoxCollider2D> a_Collider, ComponentHandle<BoxCollider2D> a_Other)
        : Collision2DMessage(a_Collider, a_Other)
    {
    }

    TriggerExit2DMessage::TriggerExit2DMessage(ComponentHandle<BoxCollider2D> a_Collider, ComponentHandle<BoxCollider2D> a_Other)
        : Collision2DMessage(a_Collider, a_Other)
    {
    }
}