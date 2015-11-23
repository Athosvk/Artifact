#include "Bullet.h"

Bullet::Bullet(BadEngine::ResourceManager& a_ResourceManager, glm::vec2 a_StartPosition) :
    m_SpriteRenderer(m_Transform, a_ResourceManager.getTexture("Textures/PNG/Bullet.png"))
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

void Bullet::updatePosition()
{
    m_Transform.translate(glm::normalize(m_TargetPosition - m_Transform.Position) * m_Speed);
}

void Bullet::setTarget(glm::vec2 a_Target)
{
    m_TargetPosition = a_Target;
    m_Transform.lookAt(m_TargetPosition);
}
