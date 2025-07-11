#pragma once
#include "../Core/MessagingSystem.h"
#include "../Core/ComponentHandle.h"

namespace Artifact
{
    class BoxCollider2D;
	
	/// <summary>
	/// Sent when two non-trigger objects have collided, for each object
	/// </summary>
	/// <seealso cref="Message" />
	class Collision2DMessage : public Message
    {
    private:		
		/// <summary>The collider that was involved in the collision</summary>
		ComponentHandle<BoxCollider2D> m_Collider;		
		/// <summary>The collider that it collided against during the collision</summary>
		ComponentHandle<BoxCollider2D> m_Other;

    public:		
		/// <summary>Initializes a new instance of the <see cref="Collision2DMessage"/> class.</summary>
		/// <param name="a_Collider">The collider involved in the collision</param>
		/// <param name="a_Other">The other collider involved in the collision</param>
		Collision2DMessage(ComponentHandle<BoxCollider2D> a_Collider, ComponentHandle<BoxCollider2D> a_Other);
		
		/// <summary>Gets the collider that was involved in the collision</summary>
		/// <returns>The involved collider</returns>
		ComponentHandle<BoxCollider2D> getCollider() const;
		
		/// <summary>Gets the other collider that was involved in the collision</summary>
		/// <returns>The other involved collider, that was collided against</returns>
		ComponentHandle<BoxCollider2D> getOther() const;
    };
	
	/// <summary>
	/// Sent when two non-trigger colliders collide with each other
	/// </summary>
	/// <seealso cref="Collision2DMessage" />
	class CollisionEnter2DMessage : public Collision2DMessage
    {
    public:		
		/// <summary>Initializes a new instance of the <see cref="CollisionEnter2DMessage"/> class.</summary>
		/// <param name="a_Collider">The collider involved in the collision</param>
		/// <param name="a_Other">The other collider involved in the collision</param>
		CollisionEnter2DMessage(ComponentHandle<BoxCollider2D> a_Collider, ComponentHandle<BoxCollider2D> a_Other);
    };
	
	/// <summary>
	/// Sent when a collider has collided with a trigger collider
	/// </summary>
	/// <seealso cref="Collision2DMessage" />
	class TriggerEnter2DMessage : public Collision2DMessage
    {
    public:		
		/// <summary>Initializes a new instance of the <see cref="TriggerEnter2DMessage"/> class.</summary>
		/// <param name="a_Collider">The a_ collider.</param>
		/// <param name="a_Other">The a_ other.</param>
		TriggerEnter2DMessage(ComponentHandle<BoxCollider2D> a_Collider, ComponentHandle<BoxCollider2D> a_Other);
    };
	
	/// <summary>
	/// Sent when the collision between two non-trigger has ended
	/// </summary>
	/// <seealso cref="Collision2DMessage" />
	class CollisionExit2DMessage : public Collision2DMessage
    {
    public:		
		/// <summary>Initializes a new instance of the <see cref="CollisionExit2DMessage"/> class.</summary>
		/// <param name="a_Collider">The collider inovlved in the collision</param>
		/// <param name="a_Other">The other collider involved in the collision</param>
		CollisionExit2DMessage(ComponentHandle<BoxCollider2D> a_Collider, ComponentHandle<BoxCollider2D> a_Other);
    };
	
	/// <summary>
	/// Sent when the collision between a collider and a trigger collider has ended
	/// </summary>
	/// <seealso cref="Collision2DMessage" />
	class TriggerExit2DMessage : public Collision2DMessage
    {
    public:		
		/// <summary>Initializes a new instance of the <see cref="TriggerExit2DMessage"/> class.</summary>
		/// <param name="a_Collider">The collider involved in the collision</param>
		/// <param name="a_Other">The other colider involved in the collision</param>
		TriggerExit2DMessage(ComponentHandle<BoxCollider2D> a_Collider, ComponentHandle<BoxCollider2D> a_Other);
    };
}
