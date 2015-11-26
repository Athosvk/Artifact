#include "Player.h"

Player::Player(BadEngine::ResourceManager& a_ResourceManager)
    : m_ResourceManager(a_ResourceManager),
    m_CharacterController(m_Transform),
    m_Renderer(m_Transform, a_ResourceManager.getTexture("Textures/PNG/CharacterLeft_Standing.png"))
{
}

Player::~Player()
{
}

void Player::update()
{
}

void Player::fixedUpdate()
{
    m_CharacterController.fixedUpdate();
}

void Player::draw(BadEngine::SpriteBatch& a_SpriteBatch)
{
    m_Renderer.draw(a_SpriteBatch);
}

Transform& Player::getTransform()
{
    return m_Transform;
}