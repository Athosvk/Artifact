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
    static const glm::vec2 BackgroundOffset;

    glm::vec2 m_Position;
    Artifact::SpriteRenderer* m_HealthRenderer;

public:
    HealthBar(Artifact::EntitySystem& a_EntitySystem, glm::vec2 a_Position);

    void update(HealthComponent* a_Health);
private:
    void initialiseHealthbar();
};

