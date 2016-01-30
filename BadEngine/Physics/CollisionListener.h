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
    };
}
