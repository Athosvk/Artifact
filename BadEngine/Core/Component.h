#pragma once
#include "GameObject.h"

namespace BadEngine
{
    class Component
    {
        GameObject m_GameObject;

    protected:
        Component(GameObject a_GameObject);
        ~Component() = default;

    public:
        template<typename T>
        T* getComponent()
        {
            return m_GameObject.getComponent<T>();
        }

        template<typename T>
        T* addComponent()
        {
            return m_GameObject.addComponent<T>();
        }
    };
}