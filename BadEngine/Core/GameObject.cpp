#include "GameObject.h"

namespace BadEngine
{
    GameObject::GameObject(unsigned a_ID)
        : m_ID(a_ID)
    {
    }

    unsigned GameObject::getID()
    {
        return m_ID;
    }
}