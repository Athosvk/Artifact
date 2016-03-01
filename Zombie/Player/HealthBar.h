#pragma once
#include <Artifact/Core/GameObject.h>

class PlayerComponent;
class HealthComponent;
namespace Artifact
{
    class SpriteRenderer;
    class EntitysSystem;
}

class HealthBar
{
private:
    static const float MaxWidth;
    static const float Height;

    Artifact::SpriteRenderer* m_HealthRenderer;

public:
    HealthBar(Artifact::EntitySystem& a_EntitySystem);

    void render(HealthComponent* a_Health);
private:
    void initialiseHealthbar();
};

