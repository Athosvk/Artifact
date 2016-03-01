#include "SpriteRenderer.h"
#include "../Transform.h"

namespace Artifact
{
    SpriteRenderer::SpriteRenderer(GameObject a_GameObject)
        : Component(a_GameObject)
    {
    }

    GLTexture* SpriteRenderer::getTexture() const
    {
        return Texture;
    }

    void SpriteRenderer::setTexture(GLTexture* a_Texture)
    {
        Texture = a_Texture;
    }
}