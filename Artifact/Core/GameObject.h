#pragma once
#include "ComponentHandle.h"

namespace Artifact
{
    class EntitySystem;
	class Transform;
	
	/// <summary>
	/// Represents an entity in the World that can contain components to be modified and read out by systems
	/// </summary>
	class GameObject
    {
    private:		
		/// <summary>The identifier of this entity, used to link it to the component it contains</summary>
		unsigned m_ID;		
		/// <summary>The reference to the entity system it belongs to</summary>
		EntitySystem& m_EntitySystem;
    protected:		
		/// <summary>The handle to the transform component of this entity</summary>
		ComponentHandle<Transform> m_Transform;

    public:		
		/// <summary>Initializes a new instance of the <see cref="GameObject"/> class.</summary>
		/// <param name="a_ID">The identifier of this entity</param>
		/// <param name="a_EntitySystem">The entity system this entity belongs to</param>
		GameObject(unsigned a_ID, EntitySystem& a_EntitySystem);
		
		/// <summary>Gets the identifier of this entity</summary>
		/// <returns>The entity's identifier</returns>
		unsigned getID() const;
		
		/// <summary>Determines whether this entity is active</summary>
		/// <returns>Whether the entity is active</returns>
		bool isActive() const;
		
		/// <summary>Activates the entity</summary>
		void activate() const;
		
		/// <summary>Deactivates the entity</summary>
		void deactivate() const;

		/// <summary>
		/// Gets the component of the specified type of this type. If it does not own a component of 
		/// the given type, it returns a NullHandle instead
		/// </summary>
		/// <returns>A handle to the component of the given type or the NullHandle</returns>
		template<typename TComponentType>
        ComponentHandle<TComponentType> getComponent() const
        {
            return m_EntitySystem.getComponent<TComponentType>(*this);
        }

		/// <summary>Gets the transform component</summary>
		/// <returns>The transform component of this entity</returns>
		template<>
        ComponentHandle<Transform> getComponent() const
        {
            return m_Transform;
        }

		/// <summary>Adds a new component of the given type</summary>
		/// <returns>A handle to the added component</returns>
		template<typename TComponentType>
        ComponentHandle<TComponentType> addComponent()
        {
            return m_EntitySystem.addComponent<TComponentType>(*this);
        }
    };
}
