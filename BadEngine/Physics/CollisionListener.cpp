#include "CollisionListener.h"

namespace BadEngine
{
    CollisionListener::CollisionListener(MessagingSystem& a_MessagingSystem)
        : m_MessagingSystem(a_MessagingSystem)
    {
    }

    void CollisionListener::BeginContact(b2Contact* a_Contact)
    {
        storeCollisionMessage<TriggerEnter2DMessage, CollisionEnter2DMessage>(a_Contact);
    }

    void CollisionListener::EndContact(b2Contact* a_Contact)
    {
        storeCollisionMessage<TriggerExit2DMessage, CollisionExit2DMessage>(a_Contact);
    }

    void CollisionListener::postStep()
    {
        m_MessagingSystem.dispatchQueue(m_CollisionQueue);
        m_CollisionQueue.clear();
    }
}