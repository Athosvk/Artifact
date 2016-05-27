#include "GameObject.h"
#include "EntitySystem.h"
#include "../Transform.h"

namespace Artifact
{
    GameObject::GameObject(unsigned a_ID, EntitySystem& a_EntitySystem)
        : m_ID(a_ID),
        m_EntitySystem(a_EntitySystem),
		m_Transform(addComponent<Transform>())
    {
    }

    unsigned GameObject::getID() const
    {
        return m_ID;
    }

    bool GameObject::isActive() const
    {
        return m_EntitySystem.isActive(*this);
    }

    void GameObject::activate() const
    {
        m_EntitySystem.activate(*this);
    }

    void GameObject::deactivate() const
    {
        m_EntitySystem.deactivate(*this);
    }
}