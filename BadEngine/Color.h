#pragma once
#include <GL/glew.h>

namespace BadEngine
{
    class Color
    {
    public:
        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
    public:
        Color(GLubyte a_RedValue, GLubyte a_GreenValue, GLubyte a_BlueValue, GLubyte a_AlphaValue);
        Color();
    };
}