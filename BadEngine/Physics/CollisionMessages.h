#pragma once
#include "../Core/MessagingSystem.h"

namespace BadEngine
{
    class BoxCollider2D;

    class CollisionEnter2DMessage : public Message
    {
    private:
        BoxCollider2D* m_Collider;
        BoxCollider2D* m_Other;

    public:
        CollisionEnter2DMessage(BoxCollider2D* a_Collider, BoxCollider2D* a_Other);

        BoxCollider2D* getCollider() const;
        BoxCollider2D* getOther() const;
    };

    class TriggerEnter2DMessage : public Message
    {
    private:
        BoxCollider2D* m_Collider;
        BoxCollider2D* m_Other;

    public:
        TriggerEnter2DMessage(BoxCollider2D a_Collider, BoxCollider2D* a_Other);

        BoxCollider2D* getCollider() const;
        BoxCollider2D* getOther() const;
    };
}
