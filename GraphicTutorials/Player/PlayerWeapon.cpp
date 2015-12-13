#include "PlayerWeapon.h"

PlayerWeapon::PlayerWeapon(const BadEngine::Mouse& a_Mouse, const Transform& a_PlayerTransform,
                           Pool<Bullet>& a_BulletPool, std::shared_ptr<BadEngine::GLTexture> a_Texture) :
    m_Mouse(a_Mouse),
    m_PlayerTransform(a_PlayerTransform),
    m_BulletPool(a_BulletPool),
    m_SpriteRenderer(m_Transform, a_Texture)
{
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
    bullet->setTarget(m_Mouse.getWorldPosition());        
}