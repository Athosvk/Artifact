#pragma once
#include <vector>
#include <BadEngine/Input/Mouse.h>
#include <BadEngine/GameTime.h>

#include "../Bullet.h"
#include "../Transform.h"
#include "../Pool.h"
#include "../SpriteRenderer.h"

class PlayerWeapon
{
private:
    const BadEngine::Mouse& m_Mouse;
    Transform m_Transform;
    const Transform& m_PlayerTransform;
    Pool<Bullet>& m_BulletPool;
    SpriteRenderer m_SpriteRenderer;
    glm::vec2 m_FireOffset = glm::vec2(-3.5f, 12.5f);
    Timer m_FireTimer;
    Timer m_CooldownTimer;
    bool m_CanFire = true;

public:
    PlayerWeapon(const BadEngine::Mouse& a_Mouse, const Transform& a_PlayerTransform, 
                 Pool<Bullet>& a_BulletPool, std::shared_ptr<BadEngine::GLTexture> a_Texture);
    ~PlayerWeapon();

    void update(const BadEngine::GameTime& a_GameTime);
    void draw(BadEngine::SpriteBatch& a_SpriteBatch) const;
    void fixedUpdate() const;
    void fire();
    void setParent(const Transform* a_Parent);
    void enableFiring();
    void disableFiring();
};
