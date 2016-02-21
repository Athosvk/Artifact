#include "GameObject.h"
#include "Component.h"
#include "EntitySystem.h"
#include "../Transform.h"

namespace BadEngine
{
    GameObject::GameObject(unsigned a_ID, EntitySystem& a_EntitySystem)
        : m_ID(a_ID),
        m_EntitySystem(a_EntitySystem)
    {
        m_Transform = addComponent<Transform>();
    }

    unsigned GameObject::getID()
    {
        return m_ID;
    }

    bool GameObject::isActive()
    {
        return m_EntitySystem.isActive(m_ID);
    }

    void GameObject::activate()
    {
        m_EntitySystem.activate(m_ID);
    }

    void GameObject::deactivate()
    {
        m_EntitySystem.deactivate(m_ID);
    }
}