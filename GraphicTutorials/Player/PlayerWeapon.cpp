#include "PlayerWeapon.h"

PlayerWeapon::PlayerWeapon(const BadEngine::Mouse& a_Mouse, BadEngine::ResourceManager& a_ResourceManager, const Transform& a_PlayerTransform)
    : m_Mouse(a_Mouse),
    m_PlayerTransform(a_PlayerTransform),
    m_ResourceManager(a_ResourceManager)
{
}

PlayerWeapon::~PlayerWeapon()
{
}

void PlayerWeapon::update()
{
    if(BadEngine::Mouse::isButtonDown(BadEngine::MouseButton::Left))
    {
        fire();
    }
}

void PlayerWeapon::draw(BadEngine::SpriteBatch& a_SpriteBatch) const
{
    for(auto bullet : m_Bullets)
    {
        bullet->draw(a_SpriteBatch);
    }
}

void PlayerWeapon::fixedUpdate() const
{
    for(auto bullet : m_Bullets)
    {
        bullet->fixedUpdate();
    }
}

void PlayerWeapon::fire()
{
    auto bullet = new Bullet(m_ResourceManager, m_PlayerTransform.Position);
    m_Bullets.push_back(bullet);
    bullet->setTarget(m_Mouse.getWorldPosition());
}