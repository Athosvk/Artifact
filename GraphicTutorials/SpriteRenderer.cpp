#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(const BadEngine::Transform& a_Transform, const std::shared_ptr<BadEngine::GLTexture> a_Texture)
    : m_Transform(a_Transform),
    Texture(a_Texture),
    Width(a_Texture->getWidth()),
    Height(a_Texture->getHeight())
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::draw(BadEngine::SpriteBatch& a_SpriteBatch) const
{
    BadEngine::Rectangle destinationRectangle(m_Transform.getPosition(), Width, Height);
    a_SpriteBatch.draw(Texture.get(), destinationRectangle, Color, UVRectangle, Depth);
}
