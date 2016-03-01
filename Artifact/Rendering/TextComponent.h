#pragma once
#include <string>

#include "SpriteFont.h"
#include "../Core/Component.h"

namespace Artifact
{
    class TextComponent : public Component
    {
    public:
        SpriteFont* Font;
        std::string Text;
        float Scaling = 0.1f;
        float Depth = 0.0f;
        Color Color = Color::White;
        EJustification Justification = EJustification::Left;

    public:
        TextComponent(GameObject a_Entity);
    };
}
