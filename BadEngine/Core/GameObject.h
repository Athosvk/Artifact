#pragma once
namespace BadEngine
{
    class EntitySystem;
    class Component;

    class GameObject
    {
    private:
        unsigned m_ID;
        EntitySystem& m_EntitySystem;

    public:
        GameObject(unsigned a_ID, EntitySystem& a_EntitySystem);

        unsigned getID();

        template<typename T>
        T getComponent()
        {
            m_EntitySystem.getComponent<T>(m_ID);
        }

        template<typename T>
        T addComponent()
        {
            m_EntitySystem.addComponent<T>(*this);
        }
    };
}
