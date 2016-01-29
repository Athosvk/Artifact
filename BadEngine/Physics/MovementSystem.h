#pragma once
#include "../Transform.h"
#include "../Core/System.h"

namespace BadEngine
{
    class MovementSystem : public BadEngine::System
    {
    public:
        MovementSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem);

        virtual void registerListeners() override;

    private:
        void updatePositions();
    };
}
