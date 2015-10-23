#include "TestSprite.h"

TestSprite::TestSprite(glm::vec2 a_Position, float a_Width, float a_Height, BadEngine::ResourceManager& a_ResourceManager) : 
    Sprite(a_Position, "Textures/PNG/CharacterRight_Walk1.png", a_Width, a_Height, a_ResourceManager)
{
}

TestSprite::~TestSprite()
{
}
