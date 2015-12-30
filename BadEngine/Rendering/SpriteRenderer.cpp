#include "SpriteRenderer.h"

namespace BadEngine
{
    SpriteRenderer::SpriteRenderer(GameObject a_GameObject)
        : Component(a_GameObject)
    {
    }

    GLTexture* SpriteRenderer::getTexture()
    {
        return Texture;
    }

    void SpriteRenderer::setTexture(GLTexture* a_Texture)
    {
        Texture = a_Texture;
        Width = a_Texture->getWidth();
        Height = a_Texture->getHeight();
    }
}