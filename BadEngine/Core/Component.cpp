#include "Component.h"
#include "GameObject.h"

namespace BadEngine
{
    Component::Component(GameObject& a_GameObject)
        : m_GameObject(a_GameObject)
    {
    }
}