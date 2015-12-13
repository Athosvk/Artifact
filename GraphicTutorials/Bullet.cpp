#include "Bullet.h"

Bullet::Bullet(BadEngine::ResourceManager& a_ResourceManager, glm::vec2 a_StartPosition) :
    m_SpriteRenderer(m_Transform, a_ResourceManager.getTexture("Textures/PNG/Bullet.png")),
    m_Timer(std::bind(&Bullet::deactivate, this), 0.8f)
{
}

Bullet::~Bullet()
{
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

void Bullet::setTarget(glm::vec2 a_Target)
{
    m_Velocity = glm::normalize(a_Target - m_Transform.Position) * m_Speed;
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
