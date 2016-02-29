#pragma once
#include <BadEngine/Core/GameObject.h>

class PlayerComponent;
class HealthComponent;
namespace BadEngine
{
    class SpriteRenderer;
    class EntitysSystem;
}

class HealthBar
{
private:
    static const float MaxWidth;
    static const float Height;

    BadEngine::SpriteRenderer* m_HealthRenderer;

public:
    HealthBar(BadEngine::EntitySystem& a_EntitySystem);

    void render(HealthComponent* a_Health);
private:
    void initialiseHealthbar();
};

