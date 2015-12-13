#include "Bullet.h"

Bullet::Bullet(const std::shared_ptr<BadEngine::GLTexture> a_Texture, glm::vec2 a_StartPosition) :
    m_SpriteRenderer(m_Transform, a_Texture),
    m_Timer(std::bind(&Bullet::deactivate, this), m_LifeTime),
    m_StartPosition(a_StartPosition)
{
}

std::unique_ptr<Bullet> Bullet::clone()
{
    auto bullet = std::make_unique<Bullet>(m_SpriteRenderer.Texture, m_StartPosition);
    bullet->m_Speed = m_Speed;
    bullet->m_LifeTime = m_LifeTime;
    bullet->m_Active = m_Active;
    return bullet;
}

void Bullet::draw(BadEngine::SpriteBatch& a_SpriteBatch) const
{
    m_SpriteRenderer.draw(a_SpriteBatch);
}

void Bullet::fixedUpdate()
{
    updatePosition();
}

void Bullet::update(const BadEngine::GameTime& a_GameTime)
{
    m_Timer.update(a_GameTime);
}

void Bullet::updatePosition()
{
    m_Transform.translate(m_Velocity);
}

void Bullet::fire(glm::vec2 a_StartPosition, glm::vec2 a_Target)
{
    m_Transform.setPosition(a_StartPosition);
    m_Velocity = glm::normalize(a_Target - m_Transform.getPosition()) * m_Speed;
    m_Transform.lookAt(a_Target);
}

void Bullet::activate()
{
    m_Active = true;
    m_Timer.reset();
}

void Bullet::deactivate()
{
    m_Active = false;
}

bool Bullet::isActive()
{
    return m_Active;
}
