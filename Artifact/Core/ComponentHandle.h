#pragma once
#include <limits>

#include "ComponentMap.h"

namespace Artifact
{
	class BaseComponentHandle
	{

	};

	template<typename TComponentType>
	class ComponentHandle : public BaseComponentHandle
	{
	private:
		static const NullIndex = std::numeric_limits<size_t>();
	public:
		static const NullHandle = ComponentHandle<TComponentType>(NullIndex, nullptr);
	private:
		size_t m_Index;
		ComponentMap<TComponentType>* m_ComponentMap;

	public:
		ComponentHandle(size_t a_Index,  ComponentMap<TComponentType>* a_ComponentMap)
			: m_ComponentMap(a_ComponentMap)
		{
		}

		TComponentType* operator->()
		{
			return &m_ComponentMap->getComponent(m_Index);
		}
	};
}
