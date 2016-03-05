#include "CollisionListener.h"

namespace Artifact
{
    CollisionListener::CollisionListener(MessagingSystem& a_MessagingSystem)
        : m_MessagingSystem(a_MessagingSystem)
    {
    }

    void CollisionListener::BeginContact(b2Contact* a_Contact)
    {
        if(canStore(a_Contact))
        {
            storeCollisionMessage<TriggerEnter2DMessage, CollisionEnter2DMessage>(a_Contact);
        }
    }

    void CollisionListener::EndContact(b2Contact* a_Contact)
    {
        if(canStore(a_Contact))
        {
            storeCollisionMessage<TriggerExit2DMessage, CollisionExit2DMessage>(a_Contact);
        }
    }

    void CollisionListener::postStep()
    {
        if(!m_CollisionQueue.isEmpty())
        {
            m_MessagingSystem.dispatchQueue(m_CollisionQueue);
            m_CollisionQueue.clear();
        }
    }

    bool CollisionListener::canStore(b2Contact* a_Contact) const
    {
        auto collider1 = static_cast<BoxCollider2D*>(a_Contact->GetFixtureA()->GetUserData());
        auto collider2 = static_cast<BoxCollider2D*>(a_Contact->GetFixtureB()->GetUserData());
        return collider1->getGameObject().isActive() && collider2->getGameObject().isActive();
    }
}