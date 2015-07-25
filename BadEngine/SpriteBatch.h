#pragma once
#include <GL/glew.h>

#include "Vertex.h"
#include "GLTexture.h"

namespace BadEngine
{
    struct Glyph
    {
    public:
        GLTexture texture;
        float depth;
        Vertex topLeft;
        Vertex bottomLeft;
        Vertex topRight;
        Vertex bottomRight;
    };

    class SpriteBatch
    {
    private:
        GLuint m_VboID = 0;
        GLuint m_VaoID = 0;

    public:
        SpriteBatch();
        ~SpriteBatch();

        void begin();
        void draw();
        void end();

    private:
        void renderBatch();
    };
}