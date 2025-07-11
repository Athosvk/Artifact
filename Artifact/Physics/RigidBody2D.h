#pragma once
#include <Box2D/Box2D.h>
#include <glm/glm.hpp>

#include "../Core/Component.h"

namespace Artifact
{
    class BoxCollider2D;
	
	/// <summary>
	/// Represents a moving object in the PhysicsWorld, that is attached to a collider
	/// </summary>
	/// <seealso cref="Component" />
	class RigidBody2D : public Component
    {
        friend class PhysicsWorld;
        friend class PhysicsSystem;
    private:		
		/// <summary>The handle to the associated Box2D body</summary>
		b2Body* m_Body = nullptr;

    public:		
		/// <summary>Initializes a new instance of the <see cref="RigidBody2D"/> class.</summary>
		/// <param name="a_GameObject">The entity to which this is attached</param>
		explicit RigidBody2D(GameObject a_GameObject);
		
		/// <summary>Gets the velocity</summary>
		/// <returns>The velocity</returns>
		glm::vec2 getVelocity() const;
		
		/// <summary>Sets the velocity</summary>
		/// <param name="a_Velocity">The new velocity</param>
		void setVelocity(glm::vec2 a_Velocity) const;
		
		/// <summary>Sets the gravity scale.</summary>
		/// <param name="a_Scale">The new gravity scale</param>
		void setGravityScale(float a_Scale) const;
		
		/// <summary>Makes the body kinematic, excluding it from collision responses, as well as other calculated forces</summary>
		void makeKinematic() const;
		
		/// <summary>Makes the body dynamic, includig it for collision responses as well as other calculated forces</summary>
		void makeDynamic() const;
		
		/// <summary>Determines whether this instance is kinematic or not</summary>
		/// <returns>Whether the body is kinematic, false if dynamic</returns>
		bool isKinematic() const;
    private:		
		/// <summary>Updates the transform state based on the physics step that took place</summary>
		void updateState() const;
    };
}
