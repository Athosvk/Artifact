#pragma once
#include "GameObject.h"

namespace Artifact
{
	/// <summary>
	/// Represents the component interface that is generally expected for every component instance to have
	/// </summary>
	class Component
    {
		/// <summary>The GameObject this Component is associated with</summary>
		GameObject m_GameObject;
		/// <summary>Whether the component is currently enabled or not</summary>
		bool m_Enabled = true;

    protected:
		/// <summary>Initializes a new instance of the <see cref="Component"/> class.</summary>
		/// <param name="a_GameObject">The entity this Component is associated with</param>
		explicit Component(GameObject a_GameObject);

    public:
		/// <summary> Retrieves a component attached to the entity this Component is associated with</summary>
        template<typename TComponentType>
        ComponentHandle<TComponentType> getComponent() const
        {
            return m_GameObject.getComponent<TComponentType>();
        }

		/// <summary> Adds a component to the entity this Component is associated with</summary>
        template<typename TComponentType>
        ComponentHandle<TComponentType> addComponent()
        {
            return m_GameObject.addComponent<TComponentType>();
        }

		/// <summary>Gets the entity this Component is associated with</summary>
		/// <returns>The associated entity</returns>
		GameObject getGameObject() const;

		/// <summary>
		/// Determines whether this component is enabled or not, so that
		/// systems can determine whether to process this component or not
		/// </summary>
		/// <returns>Whether the component is enabled</returns>
		bool isEnabled() const;

		/// <summary>Enables this instance</summary>
		void enable();

		/// <summary>Disables this instance</summary>
		void disable();
    };
}
