#pragma once
#include <BadEngine/Core/System.h>

namespace BadEngine
{
    class BoxCollider2D;
}

class BulletSystem : public BadEngine::System
{
public:
    BulletSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MesssagingSystem);

    virtual void registerListeners() override;
private:
    void registerCollisionListener(const BadEngine::GameObject a_Target);
    void onTriggerEnter(BadEngine::BoxCollider2D* a_Collider, BadEngine::BoxCollider2D* a_Other);
};
