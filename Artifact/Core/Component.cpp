#include "Component.h"

namespace Artifact
{
    Component::Component(GameObject a_GameObject)
        : m_GameObject(a_GameObject)
    {
    }

    GameObject Component::getGameObject() const
    {
        return m_GameObject;
    }

    bool Component::isEnabled() const
    {
        return m_Enabled;
    }

    void Component::enable()
    {
        m_Enabled = true;
    }

    void Component::disable()
    {
        m_Enabled = false;
    }
}