#pragma once
#include "ComponentMap.h"

namespace Artifact
{
	template<typename TComponentType>
	class ComponentHandle
	{
	private:
		size_t m_Index;
		ComponentMap<TComponentType>& m_ComponentMap;

	public:
		ComponentHandle(size_t a_Index,  ComponentMap<TComponentType>& a_ComponentMap)
			: m_ComponentMap(a_ComponentMap)
		{
		}

		TComponentType* operator->()
		{
			return &m_ComponentMap.getComponent(m_Index);
		}
	};
}
