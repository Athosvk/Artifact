#pragma once

namespace BadEngine
{
    class GameObject
    {
    private:
        unsigned m_ID;

    public:
        GameObject(unsigned a_ID);

        unsigned getID();
    };
}
