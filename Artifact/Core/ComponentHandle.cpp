#include "ComponentHandle.h"

namespace Artifact
{
	template<typename TComponentType>
	size_t ComponentHandle<TComponentType>::NullIndex = std::numeric_limits<size_t>();
	
	template<typename TComponentType>
	ComponentHandle<TComponentType> ComponentHandle<TComponentType>::NullHandle =
		ComponentHandle<TComponentType>(NullIndex, nullptr);
}