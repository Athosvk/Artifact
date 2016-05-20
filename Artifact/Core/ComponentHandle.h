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
		ComponentHandle(size_t a_Index, ComponentMap<TComponentType>* a_ComponentMap)
			: m_Index(a_Index),
			m_ComponentMap(a_ComponentMap)
		{
		}

		bool operator==(const ComponentHandle<TComponentType>& a_Other)
		{
			return m_Index == a_Other.m_Index && m_ComponentMap == a_Other.m_ComponentMap;
		}

		TComponentType* operator ->() const
		{
			return &m_ComponentMap->getComponent(m_Index);
		}
	};

	template<typename TComponentType>
	const size_t ComponentHandle<TComponentType>::NullIndex = std::numeric_limits<size_t>::max();

	template<typename TComponentType>
	const ComponentHandle<TComponentType> ComponentHandle<TComponentType>::NullHandle =
		ComponentHandle<TComponentType>(NullIndex, nullptr);

	template<typename TComponentType>
	bool operator ==(ComponentHandle<TComponentType> a_Handle, std::nullptr_t)
	{
		return a_Handle == ComponentHandle<TComponentType>::NullHandle;
	}

	template<typename TComponentType>
	bool operator ==(std::nullptr_t, ComponentHandle<TComponentType> a_Handle)
	{
		return a_Handle == nullptr;
	}

	template<typename TComponentType>
	bool operator !=(ComponentHandle<TComponentType> a_Handle, std::nullptr_t)
	{
		return !(a_Handle == nullptr);
	}

	template<typename TComponentType>
	bool operator !=(std::nullptr_t, ComponentHandle<TComponentType> a_Handle)
	{
		return !(a_Handle == nullptr);
	}
}
