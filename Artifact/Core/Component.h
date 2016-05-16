#pragma once
#include "GameObject.h"

namespace Artifact
{
    class Component
    {
        GameObject m_GameObject;
        bool m_Enabled = true;

    protected:
        Component(GameObject a_GameObject);

    public:
        template<typename TComponentType>
        ComponentHandle<TComponentType> getComponent() const
        {
            return m_GameObject.getComponent<TComponentType>();
        }

        template<typename TComponentType>
        ComponentHandle<TComponentType> addComponent()
        {
            return m_GameObject.addComponent<TComponentType>();
        }

        GameObject getGameObject() const;
        bool isEnabled() const;
        void enable();
        void disable();
    };
}
