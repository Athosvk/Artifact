#pragma once
#include "../Core/Component.h"
#include "../GL/GLTexture.h"
#include "../Color.h"
#include "../Rectangle.h"

namespace Artifact
{
    class SpriteRenderer : public Component
    {
    private:
        GLTexture* Texture;

    public:
        float Width;
        float Height;
        Artifact::Color Color = Artifact::Color::White;
        Artifact::Rectangle UVRectangle = Artifact::Rectangle(glm::vec2(0.0f, 0.0f), 1.0f, 1.0f);
        float Depth = 0.0f;
        glm::vec2 Pivot = glm::vec2(0.5f, 0.5f);

    public:
        SpriteRenderer(GameObject a_GameObject);

        GLTexture* getTexture() const;
        void setTexture(GLTexture* a_Texture);
    };
}
