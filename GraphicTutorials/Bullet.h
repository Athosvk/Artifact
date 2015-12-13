#pragma once
#include <BadEngine/IO/ResourceManager.h>
#include <BadEngine/Rendering/SpriteBatch.h>

#include "SpriteRenderer.h"
#include "Transform.h"
#include "Timer.h"

class Bullet
{
private:
    Transform m_Transform;
    SpriteRenderer m_SpriteRenderer;
    glm::vec2 m_Velocity;
    glm::vec2 m_StartPosition;
    float m_Speed = 5.0f;
    float m_LifeTime = 1.0f;
    bool m_Active = true;
    Timer m_Timer;

public:
    Bullet(const std::shared_ptr<BadEngine::GLTexture> a_Texture, glm::vec2 a_StartPosition);

    void draw(BadEngine::SpriteBatch& a_SpriteBatch) const;
    void update(const BadEngine::GameTime& a_GameTime);
    std::unique_ptr<Bullet> clone();
    void fixedUpdate();
    void setTarget(glm::vec2 a_Target);
    void activate();
    void deactivate();
    bool isActive();

private:
    void updatePosition();
};
