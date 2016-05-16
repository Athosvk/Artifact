#pragma once
#include <vector>

namespace Artifact
{
	class GameObject;

	class BaseComponentMap
	{
	protected:
		BaseComponentMap() = default;
	public:
		virtual ~BaseComponentMap() = default;
	};

	template<typename TComponentType>
	class ComponentMap : public BaseComponentMap
	{
	private:
		std::vector<TComponentType> m_Components;

	public:
		size_t addComponent(GameObject& a_GameObject)
		{
			m_Components.emplace_back(a_GameObject);
			return m_Components.size() - 1;
		}

		TComponentType& getComponent(size_t a_Index)
		{
			return m_Components[a_Index];
		}
	};
}