#pragma once
#include <Box2D/Box2D.h>
#include <glm/glm.hpp>

#include "../Core/Component.h"

namespace Artifact
{	
	/// <summary>
	/// Provides a way to perform 2D box-shaped collisions
	/// </summary>
	/// <seealso cref="Component" />
	class BoxCollider2D : public Component
    {
        //TODO: Split up in internal collider and external interface to limit friend access
        //PhysicsSystem is friended to simplify the interface for regular users. Some functions are not necessary for 
        //anything else than the PhysicsSystem
        friend class PhysicsWorld;
        friend class PhysicsSystem;
    private:		
		/// <summary>The handle to the Box2D body</summary>
		b2Body* m_Body = nullptr;		
		/// <summary>The handle to the fixture of the Box2D body</summary>
		b2Fixture* m_Fixture = nullptr;		
		/// <summary>The shape of the fixture associated</summary>
		b2PolygonShape m_Shape;		
		/// <summary>Whether the shape is dirty, due to a change in width or height</summary>
		bool m_ShapeDirty = true;		
		/// <summary>The dimensions of the collider</summary>
		glm::vec2 m_Dimensions = glm::vec2(0, 0);		
		/// <summary>The fixture definition for recreating a fixture</summary>
		b2FixtureDef m_FixtureDefinition;		
		/// <summary>The layer the collider belongs to, for selectively ignoring and identifying collisions</summary>
		uint16 m_Layer = 0;		
		/// <summary>The mask for the collider, against which collisions will be compared</summary>
		uint16 m_Mask = 0;
		/// <summary> A handle to the GameObject, so that it can be stored as userdata in the b2Body </summary>
		std::shared_ptr<GameObject> m_GameObjectHandle;

    public:		
		/// <summary>Initializes a new instance of the <see cref="BoxCollider2D"/> class.</summary>
		/// <param name="a_GameObject">The game object to attach the collider to</param>
		explicit BoxCollider2D(GameObject a_GameObject);

		/// <summary>Finalizes an instance of the <see cref="BoxCollider2D"/> class.</summary>
		~BoxCollider2D();
		
		/// <summary>Gets the dimensions of the collider</summary>
		/// <returns>The collider's dimensions</returns>
		glm::vec2 getDimensions() const;
		
		/// <summary>Sets the dimensions of the collider</summary>
		/// <param name="a_Dimensions">The collider's dimensions</param>
		void setDimensions(glm::vec2 a_Dimensions);
		
		/// <summary>Determines whether this instance is trigger collider, one without collision response</summary>
		/// <returns>Whether the collider is a trigger</returns>
		bool isTrigger() const;
		
		/// <summary>Makes the collider a trigger, making it not participate in collision responses</summary>
		void enableTriggerState();
		
		/// <summary>Makes the collider a regular collider, making ti participate in collision responses</summary>
		void disableTriggerState();
		
		/// <summary>Gets the collision layer of the collider</summary>
		/// <returns>The collision layer the collider is on</returns>
		uint16 getLayer() const;
		
		/// <summary>Sets the collision layer of the collider</summary>
		/// <param name="a_Layer">The collision layer the collider should be on</param>
		void setLayer(uint16 a_Layer);
		
		/// <summary>Gets the collision mask that should be checked against to determine collisions from being excepted</summary>
		/// <returns>The collision mask</returns>
		uint16 getMask() const;
		
		/// <summary>Sets the collision mask that should be checked against to determine collisions from being excepted </summary>
		/// <param name="a_Mask">The collision mask</param>
		void setMask(uint16 a_Mask);

    private:		
		/// <summary>Attaches or re-attaches the fixture, constructed from the stored fixture definition</summary>
		void attachFixture();
		
		/// <summary>Refreshes the fixture data that can be updated dynamically, based on state changes</summary>
		void refreshFixtureData() const;
		
		/// <summary>Executes logic related to things that should occur before the physics update</summary>
		void onPrePhysicsUpdate();
    };
}
