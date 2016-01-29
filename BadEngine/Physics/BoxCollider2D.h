#pragma once
#include <Box2D/Box2D.h>

#include "../Core/Component.h"

namespace BadEngine
{
    class BoxCollider2D : public Component
    {
        //TODO: Split up in internal collider and external interface to limit friend access
        //PhysicsSystem is friended to simplify the interface for regular users. Some functions are not necessary for 
        //anything else than the PhysicsSystem
        friend class PhysicsSystem;
    private:
        b2Body* m_Body = nullptr;
        b2Fixture* m_Fixture = nullptr;
        b2PolygonShape m_Shape;
        float m_Width = 0.0f;
        float m_Height = 0.0f;

    public:
        BoxCollider2D(GameObject a_GameObject);
        ~BoxCollider2D();

        float getWidth() const;
        float getHeight() const;
        void setWidth(float a_Width);
        void setHeight(float a_Height);

    private:
        const b2PolygonShape* getShape() const;
    };
}
