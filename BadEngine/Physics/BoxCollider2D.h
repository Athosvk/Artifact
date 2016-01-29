#pragma once
#include <Box2D/Box2D.h>
#include <glm\glm.hpp>

#include "../Core/Component.h"

namespace BadEngine
{
    class BoxCollider2D : public Component
    {
        //TODO: Split up in internal collider and external interface to limit friend access
        //PhysicsSystem is friended to simplify the interface for regular users. Some functions are not necessary for 
        //anything else than the PhysicsSystem
        friend class PhysicsWorld;
    private:
        b2Body* m_Body = nullptr;
        b2Fixture* m_Fixture = nullptr;
        b2PolygonShape m_Shape;
        bool m_ShapeDirty = true;
        glm::vec2 m_Dimensions = glm::vec2(0, 0);

    public:
        BoxCollider2D(GameObject a_GameObject);
        ~BoxCollider2D();

        glm::vec2 getDimensions() const;
        void setDimensions(glm::vec2 a_Dimensions);

    private:
        void createFixture();
        void onPrePhysicsUpdate();
    };
}
