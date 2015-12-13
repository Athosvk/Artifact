#include "PlayerWeapon.h"

PlayerWeapon::PlayerWeapon(const BadEngine::Mouse& a_Mouse, BadEngine::ResourceManager& a_ResourceManager, const Transform& a_PlayerTransform,
                           const Pool<Bullet>& a_BulletPool)
    : m_Mouse(a_Mouse),
    m_PlayerTransform(a_PlayerTransform),
    m_ResourceManager(a_ResourceManager),
    m_BulletPool(a_BulletPool)
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

}

void PlayerWeapon::fixedUpdate() const
{

}

void PlayerWeapon::fire()
{
    auto bullet = new Bullet(m_ResourceManager, m_PlayerTransform.Position);
    bullet->setTarget(m_Mouse.getWorldPosition());
}