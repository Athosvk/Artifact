#include <algorithm>
#include <functional>

#include "SpriteBatch.h"
#include "../MathHelper.h"

namespace Artifact
{
    const std::string SpriteBatch::s_DefaultVertexShader = "Vertex shaders/StandardTextured.vert";
    const std::string SpriteBatch::s_DefaultFragmentShader = "Fragment shaders/StandardTextured.frag";

    SpriteBatch::RenderBatch::RenderBatch(const GLTexture* a_Texture, GLuint a_Offset, GLuint a_IndexCount)
        : Texture(a_Texture),
        Offset(a_Offset),
        IndexCount(a_IndexCount)
    {
    }

    SpriteBatch::Glyph::Glyph(const GLTexture* a_Texture, const Rectangle& a_DestinationRectangle, Color a_Color, 
                              const Rectangle& a_UVRectangle, float a_Depth) :
                              Texture(a_Texture),
                              Depth(a_Depth),
                              TopLeft(Vertex(a_DestinationRectangle.getTopLeft(), a_Color, a_UVRectangle.getTopLeft())),
                              TopRight(Vertex(a_DestinationRectangle.getTopRight(), a_Color, a_UVRectangle.getTopRight())),
                              BottomLeft(Vertex(a_DestinationRectangle.getBottomLeft(), a_Color, a_UVRectangle.getBottomLeft())),
                              BottomRight(Vertex(a_DestinationRectangle.getBottomRight(), a_Color, a_UVRectangle.getBottomRight()))
    {
    }

    SpriteBatch::Glyph::Glyph(const GLTexture* a_Texture, const Rectangle& a_DestinationRectangle, float a_Rotation, 
                              glm::vec2 a_Origin, Color a_Color, const Rectangle& a_UVRectangle, float a_Depth) :
                              Texture(a_Texture),
                              Depth(a_Depth),
                              TopLeft(MathHelper::rotate(a_DestinationRectangle.getTopLeft(), a_Rotation, a_Origin),
                              a_Color, a_UVRectangle.getTopLeft()),
                              TopRight(MathHelper::rotate(a_DestinationRectangle.getTopRight(), a_Rotation, a_Origin),
                              a_Color, a_UVRectangle.getTopRight()),
                              BottomLeft(MathHelper::rotate(a_DestinationRectangle.getBottomLeft(), a_Rotation, a_Origin),
                              a_Color, a_UVRectangle.getBottomLeft()),
                              BottomRight(MathHelper::rotate(a_DestinationRectangle.getBottomRight(), a_Rotation, a_Origin),
                              a_Color, a_UVRectangle.getBottomRight())
    {
        //Use rotation matrix instead
    }

    SpriteBatch::SpriteBatch() :
        m_ShaderProgram(GLSLProgram(s_DefaultVertexShader, s_DefaultFragmentShader)),
        m_IBO(EBufferUsage::Dynamic)
    {
        constructVAO();
        initShaders();
    }

    void SpriteBatch::clear()
    {
        m_RenderBatches.clear();
        m_Glyphs.clear();
    }

    void SpriteBatch::begin(glm::mat4 a_ViewProjectionMatrix, ESpriteSortMode a_SpriteSortMode)
    {
        m_ViewProjectionMatrix = a_ViewProjectionMatrix;
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
            constructIBO();
            constructVBO();
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

    void SpriteBatch::draw(const GLTexture* a_Texture, const Rectangle& a_DestinationRectangle,
                           Color a_Color, const Rectangle& a_UVRectangle, float a_Depth)
    {        
        m_Glyphs.push_back(Glyph(a_Texture, a_DestinationRectangle, a_Color, a_UVRectangle, a_Depth));
    }

    void SpriteBatch::draw(const GLTexture* a_Texture, glm::vec2 a_Position, Color a_Color,
                           const Rectangle& a_UVRectangle, float a_Depth)
    {
        Rectangle destinationRectangle(a_Position, a_Texture->getWidth(), a_Texture->getHeight());
        draw(a_Texture, destinationRectangle, a_Color, a_UVRectangle, a_Depth);
    }

    void SpriteBatch::draw(const GLTexture* a_Texture, const Rectangle& a_DestinationRectangle, float a_Rotation,
                           glm::vec2 a_Origin, Color a_Color, const Rectangle& a_UVRectangle, float a_Depth)
    {
        m_Glyphs.push_back(Glyph(a_Texture, a_DestinationRectangle, a_Rotation,
            a_Origin, a_Color, a_UVRectangle, a_Depth));
    }

    void SpriteBatch::draw(const GLTexture* a_Texture, glm::vec2 a_Position, float a_Rotation,
                           glm::vec2 a_Origin, Color a_Color, const Rectangle& a_UVRectangle, float a_Depth)
    {
        Rectangle destinationRectangle(a_Position, a_Texture->getWidth(), a_Texture->getHeight());
        draw(a_Texture, destinationRectangle, a_Rotation, a_Origin, a_Color, a_UVRectangle, a_Depth);
    }

    void SpriteBatch::constructVAO() const
    {
        m_VAO.bind();
        m_VBO.bind();
        m_IBO.bind();

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
        m_IBO.unbind();
    }

    void SpriteBatch::constructIBO() 
    {
        const auto IndicesPerSprite = 6u;
        const auto VerticesPerSprite = 4u;

        std::vector<GLuint> indices;
        indices.reserve(IndicesPerSprite * m_Glyphs.size());

        for(decltype(m_Glyphs.size()) i = 0; i < m_Glyphs.size(); ++i)
        {
            auto indexOffset = i * VerticesPerSprite;

            indices.push_back(2 + indexOffset);
            indices.push_back(1 + indexOffset);
            indices.push_back(0 + indexOffset);
            indices.push_back(0 + indexOffset);
            indices.push_back(2 + indexOffset);
            indices.push_back(3 + indexOffset);
        }
        m_IBO.setData(indices);
    }

    void SpriteBatch::sortGlyphs()
    {
        std::function<bool(Glyph const&, Glyph const&)> sortFunction;
        switch(m_SortMode)
        {
        case ESpriteSortMode::BackToFront:
            sortFunction = { [](Glyph const& a_Value1, Glyph const& a_Value2)
            {
                return a_Value1.Depth < a_Value2.Depth;
            } };
            break;
        case ESpriteSortMode::FrontToBack:
            sortFunction = { [](Glyph const& a_Value1, Glyph const& a_Value2)
            {
                return a_Value1.Depth > a_Value2.Depth;
            } };
            break;
        case ESpriteSortMode::Texture:
            sortFunction = { [](Glyph const& a_Value1, Glyph const& a_Value2)
            {
                return *(a_Value1.Texture) < *(a_Value2.Texture);
            } };
            break;
        }

        std::sort(m_Glyphs.begin(), m_Glyphs.end(), sortFunction);
    }

    void SpriteBatch::bindUniforms() const
    {
        glActiveTexture(GL_TEXTURE0);

        auto textureLocation = m_ShaderProgram.getUniformLocation("sampler");
        glUniform1i(textureLocation, 0);

        auto cameraTransformLocation = m_ShaderProgram.getUniformLocation("cameraTransform");
        glUniformMatrix4fv(cameraTransformLocation, 1, GL_FALSE, &(m_ViewProjectionMatrix)[0][0]);
    }

    void SpriteBatch::renderBatches() const
    {
        m_VAO.bind();
        m_ShaderProgram.enable();
        
        bindUniforms();

        for(auto renderBatch : m_RenderBatches)
        {
            renderBatch.Texture->bind();
            m_IBO.draw(renderBatch.IndexCount, renderBatch.Offset);
        }
        m_ShaderProgram.disable();
        m_VAO.unbind();
    }

    void SpriteBatch::constructVBO() const
    {
        const auto VerticesPerSprite = 4;

        std::vector<Vertex> vertices;
        vertices.reserve(m_Glyphs.size() * VerticesPerSprite);

        for(decltype(m_Glyphs.size()) i = 0; i < m_Glyphs.size(); ++i)
        {
            vertices.push_back(m_Glyphs[i].BottomLeft);
            vertices.push_back(m_Glyphs[i].BottomRight);
            vertices.push_back(m_Glyphs[i].TopRight);
            vertices.push_back(m_Glyphs[i].TopLeft);
        }
        m_VBO.uploadData(vertices);
    }

    void SpriteBatch::createRenderBatches()
    {
        const auto IndicesPerSprite = 6;

        auto currentOffset = 0;

        for(decltype(m_Glyphs.size()) i = 0; i < m_Glyphs.size(); ++i)
        {
            if(i == 0 || *(m_Glyphs[i].Texture) != *(m_Glyphs[i - 1].Texture))
            {
                m_RenderBatches.emplace_back(m_Glyphs[i].Texture, currentOffset);
            }
            
            m_RenderBatches.back().IndexCount += IndicesPerSprite;
            currentOffset += IndicesPerSprite;
        }
    }
}