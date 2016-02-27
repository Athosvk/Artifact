#pragma once
#include <Box2D/Box2D.h>

#include "../Core/MessagingSystem.h"
#include "../Core/MessageQueue.h"
#include "CollisionMessages.h"
#include "BoxCollider2D.h"

namespace BadEngine
{
    class CollisionListener : public b2ContactListener
    {
    private:
        MessagingSystem& m_MessagingSystem;
        MessageQueue m_CollisionQueue;

    public:
        CollisionListener(MessagingSystem& a_MessagingSystem);

        virtual void BeginContact(b2Contact* a_Contact) override;
        virtual void EndContact(b2Contact* a_Contact) override;
        void postStep();
    private:
        template<typename TTriggerMessageType, typename TCollisionMessageType>
        void storeCollisionMessage(b2Contact* a_Contact)
        {
            auto collider1 = static_cast<BoxCollider2D*>(a_Contact->GetFixtureA()->GetUserData());
            auto collider2 = static_cast<BoxCollider2D*>(a_Contact->GetFixtureB()->GetUserData());
            if(collider1->isTrigger() || collider2->isTrigger())
            {
                m_CollisionQueue.enqueue<TTriggerMessageType>(collider1->getGameObject(), collider1, collider2);
            }
            else
            {
                m_CollisionQueue.enqueue<TCollisionMessageType>(collider1->getGameObject(), collider1, collider2);
            }
        }

        bool canStore(b2Contact* a_Contact) const;
    };
}
