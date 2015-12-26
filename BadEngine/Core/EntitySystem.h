#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>

namespace BadEngine
{
    class GameObject;
    class Component;

    class EntitySystem
    {
    private:
        std::unordered_map<std::type_index, std::unordered_map<unsigned, std::unique_ptr<Component>>> m_Components;
        unsigned m_LastID = 0;

    public:
        EntitySystem();
        ~EntitySystem();

        template<typename T>
        T* addComponent(GameObject& a_GameObject)
        {
            std::unique_ptr<Component> newComponent = std::make_unique<T>(a_GameObject);
            T* componentHandle = static_cast<T*>(newComponent.get());
            m_Components[std::type_index(typeid(T))].emplace(a_GameObject.getID(), std::move(newComponent));
            return componentHandle;
        }

        template<typename T>
        T* getComponent(unsigned a_GameObjectID)
        {
            auto& componentMap = m_Components[typeid(T)];
            auto iterator = componentMap.find(a_GameObjectID);
            return iterator != componentMap.end() ? static_cast<T*>(iterator->second.get()) : nullptr;
        }

        template<typename T>
        std::vector<T*> getComponentsOfType()
        {
            auto& componentMap = m_Components[typeid(T)];
            std::vector<T*> components;
            for(auto& keyValue : componentMap)
            {
                components.push_back(static_cast<T*>(keyValue.second.get()));
            }
            return components;
        }

        unsigned generateNextID();
    };
}