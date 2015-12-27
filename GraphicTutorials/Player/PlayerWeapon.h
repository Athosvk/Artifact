#pragma once
#include <vector>
#include <BadEngine/Input/Mouse.h>
#include <BadEngine/GameTime.h>
#include <BadEngine/Transform.h>

#include "../Bullet.h"
#include "../Pool.h"
#include "../SpriteRenderer.h"

class PlayerWeapon
{
private:
    const BadEngine::Mouse& m_Mouse;
    BadEngine::Transform m_Transform;
    const BadEngine::Transform& m_PlayerTransform;
    Pool<Bullet>& m_BulletPool;
    SpriteRenderer m_SpriteRenderer;
    glm::vec2 m_FireOffset = glm::vec2(-3.5f, 12.5f);
    Timer m_ReloadTimer;
    int m_ClipSize = 100;
    int m_BulletsLeft = m_ClipSize;

public:
    PlayerWeapon(const BadEngine::Mouse& a_Mouse, const BadEngine::Transform& a_PlayerTransform,
                 Pool<Bullet>& a_BulletPool, std::shared_ptr<BadEngine::GLTexture> a_Texture);
    ~PlayerWeapon();

    void update(const BadEngine::GameTime& a_GameTime);
    void draw(BadEngine::SpriteBatch& a_SpriteBatch) const;
    void fire();
    void setParent(const BadEngine::Transform* a_Parent);
    void startReload();
    void onReloadDone();
};
