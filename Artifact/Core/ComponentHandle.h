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
		static const size_t NullIndex;
	public:
		static const ComponentHandle<TComponentType> NullHandle;
	private:
		size_t m_Index;
		ComponentMap<TComponentType>* m_ComponentMap;

	public:
		ComponentHandle(size_t a_Index,  ComponentMap<TComponentType>* a_ComponentMap)
			: m_ComponentMap(a_ComponentMap)
		{
		}

		TComponentType* operator-> ()
		{
			return &m_ComponentMap->getComponent(m_Index);
		}
	};

	template<typename TComponentType>
	bool operator ==(ComponentHandle<TComponentType> a_Handle, std::nullptr_t a_Null)
	{
		return this == ComponentHandle<TComponentType>::NullHandle;
	}

	template<typename TComponentType>
	bool operator ==(std::nullptr_t a_Null, ComponentHandle<TComponentType> a_Handle)
	{
		return a_Handle == nullptr;
	}

	template<typename TComponentType>
	bool operator !=(ComponentHandle<TComponentType> a_Handle, std::nullptr_t a_Null)
	{
		return !(a_Handle == nullptr);
	}

	template<typename TComponentType>
	bool operator !=(std::nullptr_t a_Null, ComponentHandle<TComponentType> a_Handle)
	{
		return !(a_Handle == nullptr);
	}
}
