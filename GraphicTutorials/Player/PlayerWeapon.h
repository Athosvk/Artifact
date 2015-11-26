#pragma once
#include <vector>
#include <BadEngine/Input/Mouse.h>

#include "../Bullet.h"
#include "../Transform.h"

class PlayerWeapon
{
private:
    const BadEngine::Mouse& m_Mouse;
    Transform m_Transform;
    const Transform& m_PlayerTransform;
    std::vector<Bullet*> m_Bullets;
    BadEngine::ResourceManager& m_ResourceManager;

public:
    PlayerWeapon(const BadEngine::Mouse& a_Mouse, BadEngine::ResourceManager& a_ResourceManager, const Transform& a_PlayerTransform);
    ~PlayerWeapon();

    void update();
    void draw(BadEngine::SpriteBatch& a_SpriteBatch) const;
    void fixedUpdate() const;
    void fire();
};
