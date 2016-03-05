#pragma once
#include <GL/glew.h>
#include <memory>

#include "Vertex.h"
#include "../GL/GLTexture.h"
#include "../Rectangle.h"
#include "../GL/VBO.h"
#include "../GL/GLSLProgram.h"
#include "Camera2D.h"
#include "../GL/VAO.h"
#include "../GL/IBO.h"

namespace Artifact
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
            const GLTexture* Texture;
            GLuint IndexCount;
            GLuint Offset;

        public:
            RenderBatch(const GLTexture* a_Texture, GLuint a_Offset, GLuint a_IndexCount = 0);
        };

        class Glyph
        {
        public:
            const GLTexture* Texture;
            float Depth;
            Vertex BottomLeft;
            Vertex BottomRight;
            Vertex TopRight;
            Vertex TopLeft;

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
        IBO m_IBO;
        std::vector<Glyph> m_Glyphs;
        std::vector<RenderBatch> m_RenderBatches;
        ESpriteSortMode m_SortMode = ESpriteSortMode::BackToFront;
        GLSLProgram m_ShaderProgram;
        glm::mat4 m_ViewProjectionMatrix;

    public:
        SpriteBatch();

        void begin(glm::mat4 a_ViewProjectionMatrix, ESpriteSortMode a_SpriteSortMode = ESpriteSortMode::BackToFront);
        void draw(const GLTexture* a_Texture, const Rectangle& a_DestinationRectangle, Color a_Color = Color::White,
                  const Rectangle& a_UVRectangle = Rectangle(glm::vec2(0, 0), 1, 1), float a_Depth = 0);
        void draw(const GLTexture* a_Texture, glm::vec2 a_Position, Color a_Color = Color::White,
                  const Rectangle& a_UVRectangle = Rectangle(glm::vec2(0, 0), 1, 1), float a_Depth = 0);
        void draw(const GLTexture* a_Texture, const Rectangle& a_DestinationRectangle, float a_Rotation, 
                  glm::vec2 a_Origin, Color a_Color = Color::White,
                  const Rectangle& a_UVRectangle = Rectangle(glm::vec2(0, 0), 1, 1), float a_Depth = 0);
        void draw(const GLTexture* a_Texture, glm::vec2 a_Position, float a_Rotation,
                  glm::vec2 a_Origin, Color a_Color = Color::White,
                  const Rectangle& a_UVRectangle = Rectangle(glm::vec2(0, 0), 1, 1), float a_Depth = 0);
        void end();

    private:
        void bindUniforms() const;
        void renderBatches() const;
        void constructVAO() const;
        void constructIBO();
        void constructVBO() const;
        void sortGlyphs();
        void createRenderBatches();
        void initShaders();
        void clear();
    };
}