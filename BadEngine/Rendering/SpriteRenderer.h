#pragma once
#include "../Core/Component.h"
#include "../GL/GLTexture.h"
#include "../Color.h"
#include "../Rectangle.h"

namespace BadEngine
{
    class SpriteRenderer : public Component
    {
    private:
        GLTexture* Texture;

    public:
        float Width;
        float Height;
        BadEngine::Color Color = BadEngine::Color::White;
        BadEngine::Rectangle UVRectangle = BadEngine::Rectangle(glm::vec2(0.0f, 0.0f), 1.0f, 1.0f);
        float Depth = 0.0f;

    public:
        SpriteRenderer(GameObject a_GameObject);

        GLTexture* getTexture() const;
        void setTexture(GLTexture* a_Texture);
    };
}
