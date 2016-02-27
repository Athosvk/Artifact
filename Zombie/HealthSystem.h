#pragma once
#include <BadEngine/Core/System.h>
#include <BadEngine/Physics/BoxCollider2D.h>

class HealthComponent;

class HealthSystem : public BadEngine::System
{
public:
    HealthSystem(BadEngine::EntitySystem& a_EntitySystem, 
        BadEngine::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void registerTriggerListener(BadEngine::GameObject a_GameObject);
    void onTriggerEnter(BadEngine::BoxCollider2D* a_Object, BadEngine::BoxCollider2D* a_Other);
    void dealDamage(HealthComponent* a_Health, int a_Damage);
    void onDeath(HealthComponent* a_Health);
};