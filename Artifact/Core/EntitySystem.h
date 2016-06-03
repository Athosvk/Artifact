#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>

#include "MessagingSystem.h"
#include "ComponentMapper.h"
#include "ComponentHandle.h"

namespace Artifact
{
	/// <summary>
	/// A message that is sent once a component has been added to some entity in the world
	/// </summary>
	/// <seealso cref="Message" />
	template<typename TComponentType>
    class ComponentAddedMessage : public Message
    {		
		/// <summary>The component added to the entity</summary>
		ComponentHandle<TComponentType> m_AddedComponent;

    public:		
		/// <summary>Initializes a new instance of the <see cref="ComponentAddedMessage"/> class.</summary>
		/// <param name="a_AddedComponent">The component that was added to the entity</param>
		explicit ComponentAddedMessage(ComponentHandle<TComponentType> a_AddedComponent)
            : m_AddedComponent(a_AddedComponent)
        {
        }
		
		/// <summary>Gets the component that was added to the entity</summary>
		/// <returns>A handle to the component that was added</returns>
		ComponentHandle<TComponentType> getAddedComponent() const
        {
            return m_AddedComponent;
        }
    };
	
	/// <summary>
	/// The messsage sent when an entity in the world has been activated
	/// </summary>
	/// <seealso cref="Message" />
	class EntityActivatedMessage : public Message
    {		
		/// <summary>The entity that was activated</summary>
		GameObject m_ActivatedEntity;

    public:		
		/// <summary>Initializes a new instance of the <see cref="EntityActivatedMessage"/> class.</summary>
		/// <param name="a_Entity">The entity that was activated</param>
		explicit EntityActivatedMessage(GameObject a_Entity);
		
		/// <summary>Gets the entity that was activated</summary>
		/// <returns>The activated entity</returns>
		GameObject getActivatedEntity() const;
    };
	
	/// <summary>
	/// The message setnw hen an entity in the world has been deactivated
	/// </summary>
	/// <seealso cref="Message" />
	class EntityDeactivatedMessage : public Message
    {		
		/// <summary>The entity that was deactivated</summary>
		GameObject m_DeactivatedEntity;
        
    public:		
		/// <summary>Initializes a new instance of the <see cref="EntityDeactivatedMessage"/> class.</summary>
		/// <param name="a_Entity">The entity that was deactivated</param>
		explicit EntityDeactivatedMessage(GameObject a_Entity);
		
		/// <summary>Gets the entity that was deactivated</summary>
		/// <returns>The deactivated entity</returns>
		GameObject getDeactivatedEntity() const;
    };
	
	/// <summary>
	/// The system controlling the creation and mapping of entities to their respective components
	/// </summary>
	class EntitySystem
    {
    private:		
		/// <summary>
		/// The state of an entity that belongs to a specific ID
		/// </summary>
		struct EntityState
        {
        public:
			/// <summary>Whether the entity is currently active or not</summary>
			bool Active = true;			
			/// <summary>The handles to the components that this entity owns</summary>
			std::unordered_map<std::type_index, std::unique_ptr<BaseComponentHandle>> ComponentHandles;
        };
		
		/// <summary>The mapping of the ID of entities to their respective state instance</summary>
		std::unordered_map<unsigned, EntityState> m_EntityStates;		
		/// <summary>The messaging system used to communicate messages around</summary>
		MessagingSystem& m_MessagingSystem;		
		/// <summary>The previously generated ID for an entity</summary>
		unsigned m_LastID = 0;		
		/// <summary>The component mapper that maps the components to their respective entities</summary>
		ComponentMapper m_ComponentMapper;

    public:		
		/// <summary>Initializes a new instance of the <see cref="EntitySystem"/> class.</summary>
		/// <param name="a_MessagingSystem">The messaging system to communicate with</param>
		explicit EntitySystem(MessagingSystem& a_MessagingSystem);

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

		/// <summary>Creates an entity of the given type</summary>
		/// <returns></returns>
		template<typename T = GameObject>
        T createEntity()
        {
            auto id = generateNextID();
            m_EntityStates.emplace(id, EntityState());
            return T(id, *(this));
        }
		
		/// <summary>Determines whether the specified entity is active</summary>
		/// <param name="a_Entity">The entity of which to check whether it is active</param>
		/// <returns>Whether the entity is active</returns>
		bool isActive(GameObject a_Entity) const;
		
		/// <summary>Activates the specified entity.</summary>
		/// <param name="a_Entity">The entity to activate</param>
		void activate(GameObject a_Entity);
		
		/// <summary>Deactivates the specified a_ enitty.</summary>
		/// <param name="a_Enitty">The a_ enitty.</param>
		void deactivate(GameObject a_Entity);

    private:		
		/// <summary>Generates the next identifier for an entity to use</summary>
		/// <returns>The generated identifier</returns>
		unsigned generateNextID();
    };
}