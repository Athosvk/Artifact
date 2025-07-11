#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>

#include "ComponentMap.h"
#include "ComponentHandle.h"

namespace Artifact
{	
	/// <summary> Maps component types to the matching ComponentMap instance </summary>
	class ComponentMapper
	{
	private:		
		/// <summary>
		/// The base type for the HandleManager class, so that pointers can be hold without knowing
		/// the underlying template type of a HandleManager instance
		/// </summary>
		class BaseHandleManager
		{
		protected:
			/// <summary> Initializes a new instance of the <see cref="BaseHandleManager"/> class. </summary>
			BaseHandleManager() = default;
		public:
			/// <summary> Finalizes an instance of the <see cref="BaseHandleManager"/> class. </summary>
			virtual ~BaseHandleManager() = default;
		};

		/// <summary>
		/// Represents a collection of component handles that can be used to distribute around for linear access
		/// </summary>
		template<typename TComponentType>
		class HandleManager : public BaseHandleManager
		{
		public:			
			/// <summary> The handles for each Component instance of TComponentType </summary>
			std::vector<ComponentHandle<TComponentType>> Handles;
		};
		
		/// <summary> The component maps ordered by component type </summary>
		std::unordered_map<std::type_index, std::unique_ptr<BaseComponentMap>> m_Components;		
		/// <summary> The handle managers ordered by component type</summary>
		std::unordered_map<std::type_index, std::unique_ptr<BaseHandleManager>> m_Handles;
		
	public:
		/// <summary> Creates and adds a component of given type to the matching ComponentMap instance </summary>
		/// <param name="a_GameObject">The GameObject to create the component for</param>
		/// <returns> A ComponentHandle to the newly created component </returns>
		template<typename TComponentType>
		ComponentHandle<TComponentType> addComponent(GameObject& a_GameObject)
		{
			auto iterator = m_Components.find(typeid(TComponentType));
			if(iterator == m_Components.end())
			{
				addType<TComponentType>();
				iterator = m_Components.find(typeid(TComponentType));
			}
			auto componentMap = static_cast<ComponentMap<TComponentType>*>(iterator->second.get());
			auto handle = ComponentHandle<TComponentType>(componentMap->addComponent(a_GameObject), componentMap);
			toHandleManager<TComponentType>(m_Handles.find(typeid(TComponentType)))->Handles.push_back(handle);
			return handle;
		}

		/// <summary> Retrieves the component handles to all the components of TComponentType </summary>
		/// <returns> The component handles </returns>
		template<typename TComponentType>
		std::vector<ComponentHandle<TComponentType>>& getComponentsOfType()
		{
			auto iterator = m_Handles.find(typeid(TComponentType));
			if(m_Handles.find(typeid(TComponentType)) == m_Handles.end())
			{
				addType<TComponentType>();
				iterator = m_Handles.find(typeid(TComponentType));
			}
			return toHandleManager<TComponentType>(iterator)->Handles;
		}

		/// <summary> 
		/// Adds the given type as a ComponentType, so that Handles and Components can be created for that type 
		/// </summary>
		template<typename TComponentType>
		void addType()
		{
			m_Components.emplace(typeid(TComponentType), std::make_unique<ComponentMap<TComponentType>>());
			m_Handles.emplace(typeid(TComponentType), std::make_unique<HandleManager<TComponentType>>());
		}
	private:
		/// <summary> Gets the matching handle manager from the given iterator </summary>
		/// <param name="a_Iterator">The iterator pointing to a BaseHandleManager </param>
		/// <returns> The raw pointer to the HandleManager </returns>
		template<typename TComponentType>
		HandleManager<TComponentType>* toHandleManager(std::unordered_map<std::type_index, 
			std::unique_ptr<BaseHandleManager>>::iterator a_Iterator)
		{
			return static_cast<HandleManager<TComponentType>*>(a_Iterator->second.get());
		}
	};
}