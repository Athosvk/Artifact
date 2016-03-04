#pragma once
#include <Box2D/Box2D.h>
#include <glm\glm.hpp>

#include "../Core/Component.h"

namespace Artifact
{
    class BoxCollider2D : public Component
    {
        //TODO: Split up in internal collider and external interface to limit friend access
        //PhysicsSystem is friended to simplify the interface for regular users. Some functions are not necessary for 
        //anything else than the PhysicsSystem
        friend class PhysicsWorld;
        friend class PhysicsSystem;
    private:
        b2Body* m_Body = nullptr;
        b2Fixture* m_Fixture = nullptr;
        b2PolygonShape m_Shape;
        bool m_ShapeDirty = true;
        glm::vec2 m_Dimensions = glm::vec2(0, 0);
        b2FixtureDef m_FixtureDefinition;
        uint16 m_Layer = 0;
        uint16 m_Mask = 0;

    public:
        BoxCollider2D(GameObject a_GameObject);
        ~BoxCollider2D();

        glm::vec2 getDimensions() const;
        void setDimensions(glm::vec2 a_Dimensions);
        bool isTrigger() const;
        void enableTriggerState();
        void disableTriggerState();
        uint16 getLayer();
        void setLayer(uint16 a_Layer);
        uint16 getMask();
        void setMask(uint16 a_Mask);

    private:
        void attachFixture();
        void refreshFixtureData();
        void onPrePhysicsUpdate();
    };
}
