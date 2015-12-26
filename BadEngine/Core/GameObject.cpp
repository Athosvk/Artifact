#include "GameObject.h"
#include "Component.h"
#include "EntitySystem.h"

namespace BadEngine
{
    GameObject::GameObject(unsigned a_ID, EntitySystem& a_EntitySystem)
        : m_ID(a_ID),
        m_EntitySystem(a_EntitySystem)
    {
    }

    unsigned GameObject::getID()
    {
        return m_ID;
    }
}