#pragma once
#include <vector>
#include <BadEngine/Input/Mouse.h>
#include <BadEngine/GameTime.h>

#include "../Bullet.h"
#include "../Transform.h"
#include "../Pool.h"

class PlayerWeapon
{
private:
    const BadEngine::Mouse& m_Mouse;
    Transform m_Transform;
    const Transform& m_PlayerTransform;
    Pool<Bullet>& m_BulletPool;

public:
    PlayerWeapon(const BadEngine::Mouse& a_Mouse, const Transform& a_PlayerTransform, 
                 Pool<Bullet>& a_BulletPool);
    ~PlayerWeapon();

    void update(const BadEngine::GameTime& a_GameTime);
    void draw(BadEngine::SpriteBatch& a_SpriteBatch) const;
    void fixedUpdate() const;
    void fire();
};
