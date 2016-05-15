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
		std::unordered_map<std::type_index, std::unique_ptr<BaseComponentMap>> m_Components;
		
	public:
		template<typename TComponentType>
		ComponentHandle<TComponentType> addComponent(GameObject a_GameObject)
		{
			auto componentMap = static_cast<ComponentMap<TComponentType>*>
				(m_Components[typeid(TComponentType)].get());
			return ComponentHandle<TComponentType>(componentMap->addComponent(a_GameObject), 
				*componentMap);
		}

		template<typename TComponentType>
		ComponentMap<TComponentType>& getComponentsOfType()
		{
			return m_Components[typeid(TComponentType)];
		}
	};
}