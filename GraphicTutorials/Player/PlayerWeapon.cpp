#include "PlayerWeapon.h"

PlayerWeapon::PlayerWeapon(const BadEngine::Mouse& a_Mouse, const Transform& a_PlayerTransform,
                           Pool<Bullet>& a_BulletPool, std::shared_ptr<BadEngine::GLTexture> a_Texture) :
    m_Mouse(a_Mouse),
    m_PlayerTransform(a_PlayerTransform),
    m_BulletPool(a_BulletPool),
    m_SpriteRenderer(m_Transform, a_Texture)
{
    m_Transform.LocalPosition = glm::vec2(-6.0f, 33.0f);
    m_SpriteRenderer.UVRectangle = BadEngine::Rectangle(glm::vec2(1.0f, 0.0f), -1.0f, 1.0f);
}

PlayerWeapon::~PlayerWeapon()
{
}

void PlayerWeapon::update(const BadEngine::GameTime& a_GameTime)
{
    if(BadEngine::Mouse::isButtonDown(BadEngine::MouseButton::Left))
    {
        fire();
    }
}

void PlayerWeapon::draw(BadEngine::SpriteBatch& a_SpriteBatch) const
{
    m_SpriteRenderer.draw(a_SpriteBatch);
}

void PlayerWeapon::fixedUpdate() const
{

}

void PlayerWeapon::fire()
{
    auto bullet = m_BulletPool.getItem();
    bullet->fire(m_Transform.getPosition(), m_Mouse.getWorldPosition());
}

void PlayerWeapon::setParent(const Transform* a_Parent)
{
    m_Transform.Parent = a_Parent;
}