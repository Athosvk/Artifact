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
    };
}
