#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>

#include "ComponentMap.h"
#include "ComponentHandle.h"
#include "GameObject.h"

namespace Artifact
{
	class ComponentMapper
	{
	private:
		class BaseHandleManager
		{
		};

		template<typename TComponentType>
		class HandleManager : public BaseHandleManager
		{
		public:
			std::vector<ComponentHandle<TComponentType>> Handles;
		};

		std::unordered_map<std::type_index, std::unique_ptr<BaseComponentMap>> m_Components;
		std::unordered_map<std::type_index, std::unique_ptr<BaseHandleManager>> m_Handles;
		
	public:
		template<typename TComponentType>
		ComponentHandle<TComponentType> addComponent(GameObject a_GameObject)
		{
			auto iterator = m_Components.find(typeid(TComponentType));
			if(iterator == m_Components.end())
			{
				addType<TComponentType>();
			}
			auto componentMap = static_cast<ComponentMap<TComponentType>*>(iterator->second.get());
			auto handle = ComponentHandle<TComponentType>(componentMap->addComponent(a_GameObject), componentMap);
			toHandleManager<TComponentType>(m_Handles.find(typeid(TComponentType)))->Handles.push_back(handle);
			return handle;
		}

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

		template<typename TComponentType>
		void addType()
		{
			m_Components.emplace(typeid(TComponentType), std::make_unique<ComponentMap<TComponentType>>());
			m_Handles.emplace(typeid(TComponentType), std::make_unique<HandleManager<TComponentType>>());
		}
	private:
		template<typename TComponentType>
		HandleManager<TComponentType>* toHandleManager(std::unordered_map<std::type_index, 
			std::unique_ptr<BaseHandleManager>>::iterator a_Iterator)
		{
			return static_cast<HandleManager<TComponentType>*>(a_Iterator->second.get());
		}
	};
}