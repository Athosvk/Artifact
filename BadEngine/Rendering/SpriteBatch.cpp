#include <algorithm>
#include <functional>

#include "SpriteBatch.h"
#include "../MathHelper.h"

namespace BadEngine
{
    const std::string SpriteBatch::s_DefaultVertexShader = "Vertex shaders/colorShading.vert";
    const std::string SpriteBatch::s_DefaultFragmentShader = "Fragment shaders/colorShading.frag";

    SpriteBatch::RenderBatch::RenderBatch(const GLTexture* a_Texture, GLuint a_VertexCount, GLuint a_Offset)
        : texture(a_Texture),
        vertexCount(a_VertexCount),
        offset(a_Offset)

    {
    }

    SpriteBatch::Glyph::Glyph(const GLTexture* a_Texture, const Rectangle& a_DestinationRectangle, Color a_Color, 
                              const Rectangle& a_UVRectangle, float a_Depth) :
                              texture(a_Texture),
                              depth(a_Depth),
                              topLeft(Vertex(a_DestinationRectangle.getTopLeft(), a_Color, a_UVRectangle.getTopLeft())),
                              topRight(Vertex(a_DestinationRectangle.getTopRight(), a_Color, a_UVRectangle.getTopRight())),
                              bottomLeft(Vertex(a_DestinationRectangle.getBottomLeft(), a_Color, a_UVRectangle.getBottomLeft())),
                              bottomRight(Vertex(a_DestinationRectangle.getBottomRight(), a_Color, a_UVRectangle.getBottomRight()))
    {
    }

    SpriteBatch::Glyph::Glyph(const GLTexture* a_Texture, const Rectangle& a_DestinationRectangle, float a_Rotation, 
                              glm::vec2 a_Origin, Color a_Color, const Rectangle& a_UVRectangle, float a_Depth) :
                              texture(a_Texture),
                              depth(a_Depth),
                              topLeft(MathHelper::rotate(a_DestinationRectangle.getTopLeft(), a_Rotation, a_Origin),
                              a_Color, a_UVRectangle.getTopLeft()),
                              topRight(MathHelper::rotate(a_DestinationRectangle.getTopRight(), a_Rotation, a_Origin),
                              a_Color, a_UVRectangle.getTopRight()),
                              bottomLeft(MathHelper::rotate(a_DestinationRectangle.getBottomLeft(), a_Rotation, a_Origin),
                              a_Color, a_UVRectangle.getBottomLeft()),
                              bottomRight(MathHelper::rotate(a_DestinationRectangle.getBottomRight(), a_Rotation, a_Origin),
                              a_Color, a_UVRectangle.getBottomRight())
    {
    }

    SpriteBatch::SpriteBatch(const Camera2D* a_Camera) :
        m_ShaderProgram(GLSLProgram(s_DefaultVertexShader, s_DefaultFragmentShader)),
        m_Camera(a_Camera)
    {
        constructVAO();
        initShaders();
    }

    SpriteBatch::~SpriteBatch()
    {
        clear();
    }

    void SpriteBatch::clear()
    {
        m_RenderBatches.clear();
        m_Glyphs.clear();
    }

    void SpriteBatch::begin(ESpriteSortMode a_SpriteSortMode)
    {
        m_SortMode = a_SpriteSortMode;
        auto previousSize = m_Glyphs.size();
        clear();
        m_Glyphs.reserve(previousSize);
    }

    void SpriteBatch::end()
    {
        if(!m_Glyphs.empty())
        {
            sortGlyphs();
            createRenderBatches();
            renderBatches();
        }
    }

    void SpriteBatch::initShaders()
    {
        m_ShaderProgram.createAndCompileShaders();
        m_ShaderProgram.addAttribute("vertexPosition");
        m_ShaderProgram.addAttribute("vertexColor");
        m_ShaderProgram.addAttribute("vertexUVCoordinate");
        m_ShaderProgram.linkShaders();
    }

    void SpriteBatch::draw(GLTexture* a_Texture, const Rectangle& a_DestinationRectangle,
                           Color a_Color, const Rectangle& a_UVRectangle, float a_Depth)
    {        
        m_Glyphs.push_back(std::make_unique<Glyph>(a_Texture, a_DestinationRectangle, a_Color, a_UVRectangle, a_Depth));
    }

    void SpriteBatch::draw(GLTexture* a_Texture, glm::vec2 a_Position, Color a_Color,
                           const Rectangle& a_UVRectangle, float a_Depth)
    {
        Rectangle destinationRectangle(a_Position, a_Texture->getWidth(), a_Texture->getHeight());
        draw(a_Texture, destinationRectangle, a_Color, a_UVRectangle, a_Depth);
    }

    void SpriteBatch::draw(GLTexture* a_Texture, const Rectangle& a_DestinationRectangle, float a_Rotation,
                           glm::vec2 a_Origin, Color a_Color, const Rectangle& a_UVRectangle, float a_Depth)
    {
        m_Glyphs.push_back(std::make_unique<Glyph>(a_Texture, a_DestinationRectangle, a_Rotation,
            a_Origin, a_Color, a_UVRectangle, a_Depth));
    }

    void SpriteBatch::draw(GLTexture* a_Texture, glm::vec2 a_Position, float a_Rotation,
                           glm::vec2 a_Origin, Color a_Color, const Rectangle& a_UVRectangle, float a_Depth)
    {
        Rectangle destinationRectangle(a_Position, a_Texture->getWidth(), a_Texture->getHeight());
        draw(a_Texture, destinationRectangle, a_Rotation, a_Origin, a_Color, a_UVRectangle);
    }

    void SpriteBatch::constructVAO() const
    {
        m_VAO.bind();
        m_VBO.bind();

        const auto AttributeCount = 3u;
        for(auto i = 0; i < AttributeCount; ++i)
        {
            glEnableVertexAttribArray(i);
        }

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uvCoordinate)));

        m_VAO.unbind();

        for(auto i = 0; i < AttributeCount; ++i)
        {
            glDisableVertexAttribArray(i);
        }
        m_VBO.unbind();
    }

    void SpriteBatch::sortGlyphs()
    {
        std::function<bool(std::unique_ptr<Glyph> const&, std::unique_ptr<Glyph> const&)> sortFunction;
        switch(m_SortMode)
        {
        case ESpriteSortMode::BackToFront:
            sortFunction = { [](std::unique_ptr<Glyph> const& a_Value1, std::unique_ptr<Glyph> const& a_Value2)
            {
                return a_Value1->depth < a_Value2->depth;
            } };
            break;
        case ESpriteSortMode::FrontToBack:
            sortFunction = { [](std::unique_ptr<Glyph> const&a_Value1, std::unique_ptr<Glyph> const& a_Value2)
            {
                return a_Value1->depth > a_Value2->depth;
            } };
            break;
        case ESpriteSortMode::Texture:
            sortFunction = { [](std::unique_ptr<Glyph> const& a_Value1, std::unique_ptr<Glyph> const& a_Value2)
            {
                return *(a_Value1->texture) < *(a_Value2->texture);
            } };
            break;
        }

        std::stable_sort(m_Glyphs.begin(), m_Glyphs.end(), sortFunction);
    }

    void SpriteBatch::bindUniforms() const
    {
        glActiveTexture(GL_TEXTURE0);

        auto textureLocation = m_ShaderProgram.getUniformLocation("sampler");
        glUniform1i(textureLocation, 0);

        auto cameraTransformLocation = m_ShaderProgram.getUniformLocation("cameraTransform");
        auto cameraTransform = m_Camera->getTransform();

        glUniformMatrix4fv(cameraTransformLocation, 1, GL_FALSE, &cameraTransform[0][0]);
    }

    void SpriteBatch::renderBatches() const
    {
        m_VAO.bind();
        m_ShaderProgram.enable();
        
        bindUniforms();

        for(auto renderBatch : m_RenderBatches)
        {
            renderBatch.texture->bind();
            glDrawArrays(GL_TRIANGLES, renderBatch.offset, renderBatch.vertexCount);
        }
        m_ShaderProgram.disable();
        m_VAO.unbind();
    }

    void SpriteBatch::createRenderBatches()
    {
        const auto VerticesPerSprite = 6;

        std::vector<Vertex> vertices(m_Glyphs.size() * VerticesPerSprite);

        auto currentVertex = 0;
        auto currentOffset = 0;
        for(unsigned int i = 0; i < m_Glyphs.size(); ++i)
        {
            if(i == 0 || *(m_Glyphs[i]->texture) != *(m_Glyphs[i - 1]->texture))
            {
                m_RenderBatches.emplace_back(m_Glyphs[i]->texture, VerticesPerSprite, currentOffset);
            }
            else
            {
                m_RenderBatches.back().vertexCount += VerticesPerSprite;
            }
            vertices[currentVertex++] = m_Glyphs[i]->topLeft;
            vertices[currentVertex++] = m_Glyphs[i]->bottomLeft;
            vertices[currentVertex++] = m_Glyphs[i]->bottomRight;
            vertices[currentVertex++] = m_Glyphs[i]->bottomRight;
            vertices[currentVertex++] = m_Glyphs[i]->topRight;
            vertices[currentVertex++] = m_Glyphs[i]->topLeft;
            currentOffset += VerticesPerSprite;
        }
        m_VBO.uploadData(vertices);
    }
}