#pragma once
#include <GL/glew.h>
#include <memory>

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
            const GLTexture* texture;
            GLuint vertexCount;
            GLuint offset;

        public:
            RenderBatch(const GLTexture* a_Texture, GLuint a_VertexCount = 0, GLuint a_Offset = 0);
        };

        class Glyph
        {
        public:
            const GLTexture* texture;
            float depth;
            Vertex topLeft;
            Vertex topRight;
            Vertex bottomLeft;
            Vertex bottomRight;

        public:
            Glyph(const GLTexture* a_Texture, const Rectangle& a_DestinationRectangle, Color a_Color, 
                  const Rectangle& a_UVRectangle, float a_Depth);

            Glyph(const GLTexture* a_Texture, const Rectangle& a_DestinationRectangle, float a_Rotation, 
                  glm::vec2 a_Origin, Color a_Color, const Rectangle& a_UVRectangle, float a_Depth);
        };

        static const std::string SpriteBatch::s_DefaultVertexShader;
        static const std::string SpriteBatch::s_DefaultFragmentShader;

        VAO m_VAO;
        VBO m_VBO;
        std::vector<std::unique_ptr<Glyph>> m_Glyphs;
        std::vector<RenderBatch> m_RenderBatches;
        ESpriteSortMode m_SortMode = ESpriteSortMode::Texture;
        GLSLProgram m_ShaderProgram;
        const Camera2D* m_Camera;

    public:
        SpriteBatch(const Camera2D* a_Camera);
        ~SpriteBatch();

        void begin(ESpriteSortMode a_SpriteSortMode = ESpriteSortMode::Texture);
        void draw(GLTexture* a_Texture, const Rectangle& a_DestinationRectangle, Color a_Color = Color::White,
                  const Rectangle& a_UVRectangle = Rectangle(glm::vec2(0, 0), 1, 1), float a_Depth = 0);
        void draw(GLTexture* a_Texture, glm::vec2 a_Position, Color a_Color = Color::White,
                  const Rectangle& a_UVRectangle = Rectangle(glm::vec2(0, 0), 1, 1), float a_Depth = 0);
        void draw(GLTexture* a_Texture, const Rectangle& a_DestinationRectangle, float a_Rotation, 
                  glm::vec2 a_Origin, Color a_Color = Color::White,
                  const Rectangle& a_UVRectangle = Rectangle(glm::vec2(0, 0), 1, 1), float a_Depth = 0);
        void draw(GLTexture* a_Texture, glm::vec2 a_Position, float a_Rotation,
                  glm::vec2 a_Origin, Color a_Color = Color::White,
                  const Rectangle& a_UVRectangle = Rectangle(glm::vec2(0, 0), 1, 1), float a_Depth = 0);
        void end();

    private:
        void bindUniforms() const;
        void renderBatches() const;
        void constructVAO() const;
        void sortGlyphs();
        void createRenderBatches();
        void initShaders();
        void clear();
    };
}