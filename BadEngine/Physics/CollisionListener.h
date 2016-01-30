#pragma once
#include <Box2D/Box2D.h>

#include "../Core/MessagingSystem.h"
#include "BoxCollider2D.h"

namespace BadEngine
{
    class CollisionListener : public b2ContactListener
    {
    private:
        MessagingSystem& m_MessagingSystem;

    public:
        CollisionListener(MessagingSystem& a_MessagingSystem);

        virtual void BeginContact(b2Contact* a_Contact) override;
        virtual void EndContact(b2Contact* a_Contact) override;
    private:
        template<typename TTriggerMessageType, typename TCollisionMessageType>
        void broadcastCollisionMessage(b2Contact* a_Contact)
        {
            auto collider1 = static_cast<BoxCollider2D*>(a_Contact->GetFixtureA()->GetUserData());
            auto collider2 = static_cast<BoxCollider2D*>(a_Contact->GetFixtureB()->GetUserData());
            if(collider1->isTrigger() || collider2->isTrigger())
            {
                sendEnterMessage<TTriggerMessageType>(collider1, collider2);
            }
            else
            {
                sendEnterMessage<TCollisionMessageType>(collider1, collider2);
            }
        }

        template<typename T>
        void sendEnterMessage(BoxCollider2D* a_Collider1, BoxCollider2D* a_Collider2)
        {
            m_MessagingSystem.broadcast<T>(a_Collider1, a_Collider2);
        }

        template<typename T>
        void sendExitMessage(BoxCollider2D* a_Collider1, BoxCollider2D* a_Collider2)
        {
            m_MessagingSystem.broadcast<T>(a_Collider1, a_Collider2);
        }
    };
}
