#pragma once

namespace BadEngine
{
    class GameObject;

    class Component
    {
        GameObject const& m_GameObject;

    protected:
        Component(GameObject& a_GameObject);
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
