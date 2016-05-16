#pragma once
#include "ComponentHandle.h"

namespace Artifact
{
    class EntitySystem;
	class Transform;

    class GameObject
    {
    private:
        unsigned m_ID;
        EntitySystem& m_EntitySystem;
    protected:
        ComponentHandle<Transform> m_Transform;

    public:
        GameObject(unsigned a_ID, EntitySystem& a_EntitySystem);

        unsigned getID();
        bool isActive();
        void activate();
        void deactivate();

        template<typename TComponentType>
        ComponentHandle<TComponentType> getComponent() const
        {
            return m_EntitySystem.getComponent<TComponentType>(*this);
        }

        template<>
        ComponentHandle<Transform> getComponent() const
        {
            return m_Transform;
        }

        template<typename TComponentType>
        ComponentHandle<TComponentType> addComponent()
        {
            return m_EntitySystem.addComponent<TComponentType>(*this);
        }
    };
}
