#pragma once
#include <GL/glew.h>

#include "Vertex.h"
#include "..\GL/GLTexture.h"
#include "..\Rectangle.h"
#include "VBO.h"
#include "..\GL/GLSLProgram.h"
#include "Camera2D.h"
#include "VAO.h"

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
        class RenderBatch
        {
        public:
            GLTexture texture;
            GLuint vertexCount;
            GLuint offset;

        public:
            RenderBatch(GLTexture a_Texture, GLuint a_VertexCount = 0, GLuint a_Offset = 0) :
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

        static const std::string SpriteBatch::s_DefaultVertexShader;
        static const std::string SpriteBatch::s_DefaultFragmentShader;

        VAO m_VAO = VAO();
        VBO m_VBO = VBO();
        std::vector<Glyph*> m_Glyphs = std::vector<Glyph*>();
        std::vector<RenderBatch> m_RenderBatches;
        ESpriteSortMode m_SortMode = ESpriteSortMode::Texture;
        GLSLProgram m_ShaderProgram;
        const Camera2D* m_Camera;

    public:
        SpriteBatch(const Camera2D* a_Camera);
        ~SpriteBatch();

        void begin(ESpriteSortMode a_SpriteSortMode = ESpriteSortMode::Texture);
        void draw(GLTexture a_Texture, const Rectangle& a_DestinationRectangle,
                  const Rectangle& a_UVRectangle, Color a_Color = Color::White, float a_Depth = 0);
        void end();

    private:
        void renderBatches() const;
        void constructVAO() const;
        void sortGlyphs();
        void createRenderBatches();
        void initShaders();
        void clear();
    };
}