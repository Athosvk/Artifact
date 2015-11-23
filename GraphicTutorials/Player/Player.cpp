#include <BadEngine/Rendering/SpriteBatch.h>

#include "Player.h"

Player::Player(const BadEngine::Mouse& a_Mouse, BadEngine::ResourceManager& a_ResourceManager)
    : m_ResourceManager(a_ResourceManager),
    m_CharacterController(m_Transform),
    m_Weapon(a_Mouse, a_ResourceManager, m_Transform),
    m_Mouse(a_Mouse),
    m_Renderer(m_Transform, a_ResourceManager.getTexture("Textures/PNG/CharacterLeft_Standing.png"))
{
}

Player::~Player()
{
}

void Player::update()
{
    m_Weapon.update();
}

void Player::fixedUpdate()
{
    m_CharacterController.fixedUpdate();
}

void Player::draw(BadEngine::SpriteBatch& a_SpriteBatch)
{
    m_Renderer.draw(a_SpriteBatch);
}