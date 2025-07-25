#include "Color.h"

namespace Artifact
{
    const Color Color::White = Color(1.0f, 1.0f, 1.0f);
    const Color Color::Black = Color(0.0f, 0.0f, 0.0f);
    const Color Color::Red = Color(1.0f, 0.0f, 0.0f);
    const Color Color::Blue = Color(0.0f, 0.0f, 1.0f);
    const Color Color::Green = Color(0.0f, 1.0f, 0.0f);
    const Color Color::Yellow = Color(0.5f, 0.5f, 0.0f);
    const Color Color::Magenta = Color(1.0f, 0.0f, 1.0f);
    const Color Color::Cyan = Color(0.0f, 1.0f, 1.0f);

    Color::Color(float a_RedValue, float a_GreenValue, float a_BlueValue, float a_AlphaValue)
		: R(a_RedValue),
		G(a_GreenValue),
		B(a_BlueValue),
		A(a_AlphaValue)
    {
    }

	bool Color::operator==(const Color& a_Color)
	{
		return a_Color.R == R && a_Color.G == G &&
			a_Color.B == B && a_Color.A == A;
	}

    Color Color::createFromRGBAValue(uint64_t a_Value)
    {
        auto newColor = Color();

        newColor.R = (a_Value >> 24 & 0xFF) / 255.0f;
        newColor.G = (a_Value >> 16 & 0xFF) / 255.0f;
        newColor.B = (a_Value >> 8 & 0xFF) / 255.0f;
        newColor.A = (a_Value & 0xFF) / 255.0f;

        return newColor;
    }
}