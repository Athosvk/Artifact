#pragma once
#include "ComponentMap.h"

namespace Artifact
{
	template<typename TComponentType>
	class ComponentHandle
	{
	private:
		size_t m_Index;
		ComponentMap<TComponentType>& m_ComponentMapper;

	public:
		ComponentHandle(size_t a_Index,  ComponentMapper<TComponentType>& a_ComponentMapper)
			: m_ComponentMapper(a_ComponentMapper)
		{
		}
	};
}
