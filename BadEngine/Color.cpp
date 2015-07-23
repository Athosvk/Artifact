#include "Color.h"

namespace BadEngine
{
    Color::Color(GLubyte a_RedValue, GLubyte a_GreenValue, GLubyte a_BlueValue, GLubyte a_AlphaValue)
    {
        r = a_RedValue;
        g = a_GreenValue;
        b = a_BlueValue;
        a = a_AlphaValue;
    }

    Color::Color()
    {

    }
}