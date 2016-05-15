#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>

#include "ComponentMap.h"

namespace Artifact
{
	class ComponentMapper
	{
	private:
		std::unordered_map<std::type_index, std::unique_ptr<BaseComponentMap>> m_Components;
	};
}