#pragma once
#include <limits>

#include "ComponentMap.h"

namespace Artifact
{	
	/// <summary>
	/// Base class for the ComponentHandle class, so you can store pointers to a ComponentHandle
	/// without knowing the underlying template type
	/// </summary>
	class BaseComponentHandle
	{
	protected:
		/// <summary> Initializes a new instance of the <see cref="BaseComponentHandle"/> class. </summary>
		BaseComponentHandle() = default;
	public:
		/// <summary> Finalizes an instance of the <see cref="BaseComponentHandle"/> class. </summary>
		virtual ~BaseComponentHandle() = default;
	};

	/// <summary>  Provides a handle to a component allocated in a ComponentMap of the given ComponentType </summary>
	template<typename TComponentType>
	class ComponentHandle : public BaseComponentHandle
	{
	private:
		/// <summary> The index for a NullHandle, similar to nullptr </summary>
		static const size_t NullIndex;
	public:	
		/// <summary> 
		/// The empty handle, pointing to no component. Used as return value for when
		/// a component is not found or as initial value 
		/// </summary>
		static const ComponentHandle<TComponentType> NullHandle;
	private:
		/// <summary> The index of the component this handle is pointing to in the ComponentMap </summary>
		size_t m_Index;	
		/// <summary> The component map that has the corresponding component stored  </summary>
		ComponentMap<TComponentType>* m_ComponentMap;

	public:		
		/// <summary> Initializes a new instance of the <see cref="ComponentHandle"/> class </summary>
		/// <param name="a_Index">Index of the component pointing to</param>
		/// <param name="a_ComponentMap">The ComponentMap that has the component stored </param>
		ComponentHandle(size_t a_Index, ComponentMap<TComponentType>* a_ComponentMap)
			: m_ComponentMap(a_ComponentMap),
			m_Index(a_Index)
		{
		}
		
		/// <summary> Compares the given ComponentHandle with this instance </summary>
		/// <param name="a_Other">The ComponentHandle to compare to</param>
		/// <returns> Whether the instances are equal </returns>
		bool operator==(const ComponentHandle<TComponentType>& a_Other)
		{
			return m_Index == a_Other.m_Index && m_ComponentMap == a_Other.m_ComponentMap;
		}
		
		/// <summary> Dereferences the ComponentHandle so that the component itself can be accessed </summary>
		/// <returns> The underlying component </returns>
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

	/// <summary> Compares a ComponentHandle with a nullpointer type </summary>
	/// <param name="a_Handle">The ComponentHandle to compare</param>
	/// <param name="a_Null">The nullptr type to compare to</param>
	/// <returns> Whether the ComponentHandle instance is equal to nullptr </returns>
	template<typename TComponentType>
	bool operator ==(ComponentHandle<TComponentType> a_Handle, std::nullptr_t a_Null)
	{
		return a_Handle == ComponentHandle<TComponentType>::NullHandle;
	}

	/// <summary> Compares a ComponentHandle with a nullpointer type </summary>
	/// <param name="a_Null">The nullptr type to compare to</param>
	/// <param name="a_Handle">The ComponentHandle to compare</param>
	/// <returns> Whether the ComponentHandle instance is equal to nullptr </returns>
	template<typename TComponentType>
	bool operator ==(std::nullptr_t a_Null, ComponentHandle<TComponentType> a_Handle)
	{
		return a_Handle == nullptr;
	}

	/// <summary> Compares a ComponentHandle with a nullpointer type </summary>
	/// <param name="a_Handle">The ComponentHandle to compare</param>
	/// <param name="a_Null">The nullptr type to compare to</param>
	/// <returns> Whether the ComponentHandle instance is not equal to nullptr </returns>
	template<typename TComponentType>
	bool operator !=(ComponentHandle<TComponentType> a_Handle, std::nullptr_t a_Null)
	{
		return !(a_Handle == nullptr);
	}

	/// <summary> Compares a ComponentHandle with a nullpointer type </summary>
	/// <param name="a_Null">The nullptr type to compare to</param>
	/// <param name="a_Handle">The ComponentHandle to compare</param>
	/// <returns> Whether the ComponentHandle instance is not equal to nullptr </returns>
	template<typename TComponentType>
	bool operator !=(std::nullptr_t a_Null, ComponentHandle<TComponentType> a_Handle)
	{
		return !(a_Handle == nullptr);
	}
}
