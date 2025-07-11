#pragma once
#include <Box2D/Box2D.h>

#include "../Core/MessagingSystem.h"
#include "../Core/MessageQueue.h"
#include "BoxCollider2D.h"
#include "../Core/EntitySystem.h"

namespace Artifact
{	
	/// <summary>
	/// Listens to collisions, so that messages can be distributed once specific collisions occur
	/// </summary>
	/// <seealso cref="b2ContactListener" />
	class CollisionListener : public b2ContactListener
    {
    private:		
		/// <summary>The messaging system to forward collision messages to</summary>
		MessagingSystem& m_MessagingSystem;
		/// <summary>The messages that have been queued/stalled until the end of the collision update</summary>
		MessageQueue m_CollisionQueue;

    public:		
		/// <summary>Initializes a new instance of the <see cref="CollisionListener"/> class.</summary>
		/// <param name="a_MessagingSystem">The a_ messaging system.</param>
		explicit CollisionListener(MessagingSystem& a_MessagingSystem);
		
		/// <summary>Called when a contact has started to take place</summary>
		/// <param name="a_Contact">The contact that is taking place</param>
		virtual void BeginContact(b2Contact* a_Contact) override;
		
		/// <summary>Called when a contact is no longer occuring</summary>
		/// <param name="a_Contact">The contact that was ended</param>
		virtual void EndContact(b2Contact* a_Contact) override;
		
		/// <summary> Performs the post collision step logic</summary>
		void postStep();
    private:
		/// <summary>Stores the collision message of the specified sort, given the type for a trigger as well as a collision message</summary>
		/// <param name="a_Contact">The contact to store the collision message for</param>
		template<typename TTriggerMessageType, typename TCollisionMessageType>
        void storeCollisionMessage(b2Contact* a_Contact)
        {
			auto collider1 = static_cast<GameObject*>(a_Contact->GetFixtureA()->
				GetUserData())->getComponent<BoxCollider2D>();
			auto collider2 = static_cast<GameObject*>(a_Contact->GetFixtureB()->
				GetUserData())->getComponent<BoxCollider2D>();
			if(collider1->isTrigger() || collider2->isTrigger())
			{
				m_CollisionQueue.enqueue<TTriggerMessageType>(collider1->getGameObject(), collider1, collider2);
				m_CollisionQueue.enqueue<TTriggerMessageType>(collider2->getGameObject(), collider2, collider1);
			}
			else
			{
				m_CollisionQueue.enqueue<TCollisionMessageType>(collider1->getGameObject(), collider1, collider2);
				m_CollisionQueue.enqueue<TCollisionMessageType>(collider2->getGameObject(), collider2, collider1);
			}
        }
		
		/// <summary>Determines whether this instance can store the specified collision message</summary>
		/// <param name="a_Contact">The contact to check for</param>
		/// <returns>Whether the contact is allowed to be stored</returns>
		bool canStore(b2Contact* a_Contact) const;
    };
}
