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
        auto collider1 = static_cast<BoxCollider2D*>(a_Contact->GetFixtureA()->GetUserData());
        auto collider2 = static_cast<BoxCollider2D*>(a_Contact->GetFixtureB()->GetUserData());
        sendCollisionMessage(collider1, collider2);
        sendCollisionMessage(collider2, collider1);
    }

    void CollisionListener::EndContact(b2Contact* a_Contact)
    {

    }

    void CollisionListener::sendCollisionMessage(BoxCollider2D* a_Collider, BoxCollider2D* a_Other)
    {
        if(a_Collider->isTrigger())
        {
            m_MessagingSystem.broadcast<TriggerEnter2DMessage>(a_Collider, a_Other);
        }
        else
        {
            m_MessagingSystem.broadcast<CollisionEnter2DMessage>(a_Collider, a_Other);
        }
    }
}