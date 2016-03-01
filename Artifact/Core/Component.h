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
        ~Component() = default;

    public:
        template<typename T>
        T* getComponent() const
        {
            return m_GameObject.getComponent<T>();
        }

        template<typename T>
        T* addComponent()
        {
            return m_GameObject.addComponent<T>();
        }

        GameObject getGameObject() const;
        bool isEnabled() const;
        void enable();
        void disable();
    };
}
