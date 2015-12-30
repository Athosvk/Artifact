#pragma once
#include "../Transform.h"
#include "../Core/System.h"

namespace BadEngine
{
    class MovementSystem : public BadEngine::System
    {
    public:
        MovementSystem(BadEngine::EntitySystem& a_EntitySystem);

        virtual void sendMessage(const BadEngine::Message* a_Message) override;

    private:
        void updatePositions();
    };
}
