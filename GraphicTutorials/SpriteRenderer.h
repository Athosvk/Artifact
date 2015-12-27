#pragma once
#include <BadEngine/Rendering/SpriteBatch.h>
#include <BadEngine/GL/GLTexture.h>
#include <BadEngine/Transform.h>

class SpriteRenderer
{
private:
    const BadEngine::Transform& m_Transform;

public:
    const std::shared_ptr<BadEngine::GLTexture> Texture;
    float Width;
    float Height;
    BadEngine::Color Color = BadEngine::Color::White;
    BadEngine::Rectangle UVRectangle = BadEngine::Rectangle(glm::vec2(0.0f, 0.0f), 1.0f, 1.0f);
    float Depth = 0.0f;

public:
    SpriteRenderer(const BadEngine::Transform& a_Transform, const std::shared_ptr<BadEngine::GLTexture> a_Texture);
    ~SpriteRenderer();

    void draw(BadEngine::SpriteBatch& a_SpriteBatch) const;
};

