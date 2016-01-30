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
        broadcastCollisionMessage<TriggerEnter2DMessage, CollisionEnter2DMessage>(a_Contact);
    }

    void CollisionListener::EndContact(b2Contact* a_Contact)
    {
        broadcastCollisionMessage<TriggerExit2DMessage, CollisionExit2DMessage>(a_Contact);
    }
}