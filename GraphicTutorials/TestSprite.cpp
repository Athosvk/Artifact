#include "TestSprite.h"

TestSprite::TestSprite(glm::vec2 a_Position, float a_Width, float a_Height) : Sprite(a_Position, "Textures/PNG/CharacterRight_Walk1.png",
                                                                a_Width, 
                                                                a_Height)
{
}

TestSprite::~TestSprite()
{
}
