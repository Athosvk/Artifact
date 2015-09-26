#pragma once
#include <GL/glew.h>

namespace BadEngine
{
    class Color
    {
    public:
        GLubyte r = 0;
        GLubyte g = 0;
        GLubyte b = 0;
        GLubyte a = 0;
    public:
        Color(GLubyte a_RedValue, GLubyte a_GreenValue, GLubyte a_BlueValue, GLubyte a_AlphaValue);
        Color();
    };
}