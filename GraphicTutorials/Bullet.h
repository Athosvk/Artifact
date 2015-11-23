#pragma once
#include <BadEngine/IO/ResourceManager.h>
#include <BadEngine/Rendering/SpriteBatch.h>

#include "SpriteRenderer.h"
#include "Transform.h"

class Bullet
{
private:
    Transform m_Transform;
    glm::vec2 m_TargetPosition;
    SpriteRenderer m_SpriteRenderer;
    float m_Speed = 1.0f;

public:
    Bullet(BadEngine::ResourceManager& a_ResourceManager, glm::vec2 a_StartPosition);
    ~Bullet();

    void draw(BadEngine::SpriteBatch& a_SpriteBatch) const;
    void fixedUpdate();
    void setTarget(glm::vec2 a_Target);

private:
    void updatePosition();
};
