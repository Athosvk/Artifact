#pragma once
namespace BadEngine
{
    class EntitySystem;

    class GameObject
    {
    private:
        unsigned m_ID;
        EntitySystem& m_EntitySystem;
        bool m_Active;

    public:
        GameObject(unsigned a_ID, EntitySystem& a_EntitySystem);

        unsigned getID();
        bool isActive();
        void activate();
        void deactivate();

        template<typename T>
        T* getComponent()
        {
            return m_EntitySystem.getComponent<T>(m_ID);
        }

        template<typename T>
        T* addComponent()
        {
            return m_EntitySystem.addComponent<T>(*this);
        }
    };
}
