#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>

#include "Component.h"
#include "MessagingSystem.h"
#include "ComponentMapper.h"
#include "ComponentHandle.h"

namespace Artifact
{
    template<typename TComponentType>
    class ComponentAddedMessage : public Message
    {
		ComponentHandle<TComponentType> m_AddedComponent;

    public:
        ComponentAddedMessage(ComponentHandle<TComponentType> a_AddedComponent)
            : m_AddedComponent(a_AddedComponent)
        {
        }

		ComponentHandle<TComponentType> getAddedComponent() const
        {
            return m_AddedComponent;
        }
    };

    class EntityActivatedMessage : public Message
    {
        GameObject m_ActivatedEntity;

    public:
        EntityActivatedMessage(GameObject a_Entity);

        GameObject getActivatedEntity() const;
    };

    class EntityDeactivatedMessage : public Message
    {
        GameObject m_DeactivatedEntity;
        
    public:
        EntityDeactivatedMessage(GameObject a_Entity);

        GameObject getDeactivatedEntity() const;
    };

    class EntitySystem
    {
    private:
        struct EntityState
        {
        public:
            bool Active = true;
			std::unordered_map<std::type_index, std::unique_ptr<BaseComponentHandle>> ComponentHandles;
        };

        //Unsigned used for game object id
        std::unordered_map<unsigned, EntityState> m_EntityStates;
        MessagingSystem& m_MessagingSystem;
        unsigned m_LastID = 0;
		ComponentMapper m_ComponentMapper;

    public:
        EntitySystem(MessagingSystem& a_MessagingSystem);

		/// <summary> Creates and adds a component of given TComponentType </summary>
		/// <param name="a_GameObject">The GameObject to create the component for</param>
		/// <returns> A ComponentHandle to the newly created component </returns>
        template<typename TComponentType>
        ComponentHandle<TComponentType> addComponent(GameObject& a_GameObject)
        {
			ComponentHandle<TComponentType> componentHandle = m_ComponentMapper.addComponent<TComponentType>(a_GameObject);
            m_MessagingSystem.broadcast<ComponentAddedMessage<TComponentType>>(componentHandle);
			auto result = m_EntityStates.at(a_GameObject.getID()).
				ComponentHandles.emplace(typeid(TComponentType), std::make_unique<ComponentHandle<TComponentType>>(componentHandle));
            return *static_cast<ComponentHandle<TComponentType>*>(result.first->second.get());
        }

		/// <summary> Returns a ComponentHandle to the GameObject's TComponentType instnace </summary>
		/// <param name="a_GameObject">The GameObject owning the component </param>
		/// <returns> A ComponentHandle to the component or a NullHandle if it does not exist</returns>
        template<typename TComponentType>
        ComponentHandle<TComponentType> getComponent(GameObject a_GameObject) const
        {
			auto entityIterator = m_EntityStates.find(a_GameObject.getID());
			auto componentIterator = entityIterator->second.ComponentHandles.find(typeid(TComponentType));
			ComponentHandle<TComponentType> handle = ComponentHandle<TComponentType>::NullHandle;
			if(componentIterator != entityIterator->second.ComponentHandles.end())
			{
				handle = *static_cast<ComponentHandle<TComponentType>*>(componentIterator->second.get());
			}
            return handle;
        }

		/// <summary> Retreives the vector of all the ComponentHandles for a given type </summary>
		/// <returns> The vector of ComponentHandle of type TComponentType </returns>
        template<typename TComponentType>
        std::vector<ComponentHandle<TComponentType>>& getComponentsOfType()
        {            
			return m_ComponentMapper.getComponentsOfType<TComponentType>();
        }

        template<typename T = GameObject>
        T createEntity()
        {
            auto id = generateNextID();
            m_EntityStates.emplace(id, EntityState());
            return T(id, *(this));
        }

        bool isActive(GameObject a_Entity);
        void activate(GameObject a_Entity);
        void deactivate(GameObject a_Enitty);

    private:
        unsigned generateNextID();
    };
}