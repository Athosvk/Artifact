#include "PlayerWeapon.h"

PlayerWeapon::PlayerWeapon(const BadEngine::Mouse& a_Mouse, const Transform& a_PlayerTransform,
                           Pool<Bullet>& a_BulletPool, std::shared_ptr<BadEngine::GLTexture> a_Texture) :
    m_Mouse(a_Mouse),
    m_PlayerTransform(a_PlayerTransform),
    m_BulletPool(a_BulletPool),
    m_SpriteRenderer(m_Transform, a_Texture),
    m_FireTimer(std::bind(&PlayerWeapon::disableFiring, this), 0.8f),
    m_CooldownTimer(nullptr, 0.3f)
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
        if(m_CanFire && m_CooldownTimer.isDone())
        {
            fire();
        }
    }
    else if(m_FireTimer.isDone())
    {
        m_FireTimer.reset();
        enableFiring();
    }
    m_FireTimer.update(a_GameTime);
    m_CooldownTimer.update(a_GameTime);
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
    bullet->fire(m_Transform.getPosition() + m_FireOffset, m_Mouse.getWorldPosition());
    m_FireTimer.start();
    m_CooldownTimer.reset();
    m_CooldownTimer.start();
}

void PlayerWeapon::setParent(const Transform* a_Parent)
{
    m_Transform.Parent = a_Parent;
}

void PlayerWeapon::enableFiring()
{
    m_CanFire = true;
}

void PlayerWeapon::disableFiring()
{
    m_CanFire = false;
}