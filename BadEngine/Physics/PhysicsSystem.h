#pragma once
#include "../Core/System.h"

namespace BadEngine
{
    class PhysicsSystem : public System
    {
    public:
        PhysicsSystem(EntitySystem& a_EntitySystem);

        virtual void sendMessage(const Message* a_Message) override;
        
    private:
        void fixedUpdate();
        void updatePositions();
    };
}
