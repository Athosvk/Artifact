#pragma once
#include <vector>

namespace Artifact
{
	class GameObject;
	
	/// <summary>
	/// The base type for the ComponentMap class, so that pointers can be hold without knowing
	/// the underlying template type of a ComponentMap instance
	/// </summary>
	class BaseComponentMap
	{
	protected:
		/// <summary> Initializes a new instance of the <see cref="BaseComponentMap"/> class. </summary>
		BaseComponentMap() = default;
	public:
		/// <summary> Finalizes an instance of the <see cref="BaseComponentMap"/> class. </summary>
		virtual ~BaseComponentMap() = default;
	};

	template<typename TComponentType>
	class ComponentMap : public BaseComponentMap
	{
	private:		
		/// <summary> The components of this ComponentMap </summary>
		std::vector<TComponentType> m_Components;

	public:		
		/// <summary> Creates an instance of the component and adds it </summary>
		/// <param name="a_GameObject">The GameObject to create the component for </param>
		/// <returns> The index of the newly created component </returns>
		size_t addComponent(GameObject& a_GameObject)
		{
			m_Components.emplace_back(a_GameObject);
			return m_Components.size() - 1;
		}
		
		/// <summary> Gets the instance of the component at the given index </summary>
		/// <param name="a_Index">Index of the component</param>
		/// <returns> A reference to the component at index a_Index </returns>
		TComponentType& getComponent(size_t a_Index)
		{
			return m_Components[a_Index];
		}
	};
}