#include "CollisionListener.h"
#include "CollisionMessages.h"

namespace BadEngine
{
    CollisionListener::CollisionListener(MessagingSystem& a_MessagingSystem)
        : m_MessagingSystem(a_MessagingSystem)
    {
    }

    void CollisionListener::BeginContact(b2Contact* a_Contact)
    {
        auto collider = static_cast<BoxCollider2D*>(a_Contact->GetFixtureA()->GetUserData());
        auto other = static_cast<BoxCollider2D*>(a_Contact->GetFixtureB()->GetUserData());
        m_MessagingSystem.broadcast<CollisionEnter2DMessage>(collider, other);
    }

    void CollisionListener::EndContact(b2Contact* a_Contact)
    {

    }
}