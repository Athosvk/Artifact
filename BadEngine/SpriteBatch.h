#pragma once
#include <GL/glew.h>

#include "Vertex.h"
#include "GLTexture.h"
#include "Rectangle.h"
#include "VBO.h"

namespace BadEngine
{
    enum class ESpriteSortMode
    {
        FrontToBack,
        BackToFront,
        Texture
    };

    class SpriteBatch
    {
    private:
        class SharedBatch
        {
        public:
            GLTexture texture;
            GLuint vertexCount;
            GLuint offset;

        public:
            SharedBatch(GLTexture a_Texture, GLuint a_VertexCount = 0, GLuint a_Offset = 0) :
                texture(a_Texture),
                vertexCount(a_VertexCount),
                offset(a_Offset)
            {
                
            }
        };

        class Glyph
        {
        public:
            GLTexture texture;
            float depth;
            Vertex topLeft;
            Vertex bottomLeft;
            Vertex topRight;
            Vertex bottomRight;

            Glyph(GLTexture a_Texture, const Rectangle& a_DestinationRectangle, const Rectangle& a_UVRectangle, Color a_Color, float a_Depth) :
                texture(a_Texture),
                depth(a_Depth),
                //Using inverted y coordinates, thus opposite vertical corners
                topLeft(Vertex(a_DestinationRectangle.getBottomLeft(), a_Color, a_UVRectangle.getBottomLeft())),
                bottomLeft(Vertex(a_DestinationRectangle.getTopLeft(), a_Color, a_UVRectangle.getTopLeft())),
                topRight(Vertex(a_DestinationRectangle.getBottomRight(), a_Color, a_UVRectangle.getBottomRight())),
                bottomRight(Vertex(a_DestinationRectangle.getTopRight(), a_Color, a_UVRectangle.getTopRight()))
            {
            };
        };

        GLuint m_VaoID = 0;
        VBO m_VBO = VBO();
        std::vector<Glyph*> m_Glyphs = std::vector<Glyph*>();
        std::vector<SharedBatch> m_RenderBatches;
        ESpriteSortMode m_SortMode = ESpriteSortMode::Texture;

    public:
        SpriteBatch();
        ~SpriteBatch();

        void begin(ESpriteSortMode a_SpriteSortMode = ESpriteSortMode::Texture);
        void draw(GLTexture a_Texture, const Rectangle& a_DestinationRectangle,
                  const Rectangle& a_UVRectangle, Color a_Color = Color::White, float a_Depth = 0);
        void end();

    private:
        void renderBatches();
        void createVAO();
        void sortGlyphs();
        void createRenderBatches();
    };
}