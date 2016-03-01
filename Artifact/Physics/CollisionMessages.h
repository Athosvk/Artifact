#pragma once
#include "../Core/MessagingSystem.h"

namespace Artifact
{
    class BoxCollider2D;

    class Collision2DMessage : public Message
    {
    private:
        BoxCollider2D* m_Collider;
        BoxCollider2D* m_Other;

    public:
        Collision2DMessage(BoxCollider2D* a_Collider, BoxCollider2D* a_Other);

        BoxCollider2D* getCollider() const;
        BoxCollider2D* getOther() const;
    };

    class CollisionEnter2DMessage : public Collision2DMessage
    {
    public:
        CollisionEnter2DMessage(BoxCollider2D* a_Collider, BoxCollider2D* a_Other);
    };

    class TriggerEnter2DMessage : public Collision2DMessage
    {
    public:
        TriggerEnter2DMessage(BoxCollider2D* a_Collider, BoxCollider2D* a_Other);
    };

    class CollisionExit2DMessage : public Collision2DMessage
    {
    public:
        CollisionExit2DMessage(BoxCollider2D* a_Collider, BoxCollider2D* a_Other);
    };

    class TriggerExit2DMessage : public Collision2DMessage
    {
    public:
        TriggerExit2DMessage(BoxCollider2D* a_Collider, BoxCollider2D* a_Other);
    };
}
