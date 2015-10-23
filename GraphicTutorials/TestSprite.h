#pragma once
#include <glm/glm.hpp>
#include <BadEngine/Sprite.h>

class TestSprite : public BadEngine::Sprite
{
public:
    TestSprite(glm::vec2 a_Position, float a_Width, float a_Height, BadEngine::ResourceManager& a_ResourceManager);
    virtual ~TestSprite() override;
};

