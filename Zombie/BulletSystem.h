#pragma once
#include <Artifact/Core/System.h>

namespace Artifact
{
    class BoxCollider2D;
}

class BulletSystem : public Artifact::System
{
public:
    BulletSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MesssagingSystem);

    virtual void registerListeners() override;
private:
    void registerCollisionListener(const Artifact::GameObject a_Target);
    void onCollisionEnter(Artifact::BoxCollider2D* a_Collider, Artifact::BoxCollider2D* a_Other);
};
