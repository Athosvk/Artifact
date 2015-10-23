#include <algorithm>
#include <functional>

#include "SpriteBatch.h"

namespace BadEngine
{
    const std::string SpriteBatch::s_DefaultVertexShader = "Vertex shaders/colorShading.vert";
    const std::string SpriteBatch::s_DefaultFragmentShader = "Fragment shaders/colorShading.frag";

    SpriteBatch::SpriteBatch(const Camera2D* a_Camera) :
        m_ShaderProgram(GLSLProgram(s_DefaultVertexShader, s_DefaultFragmentShader)),
        m_Camera(a_Camera)
    {
        createVAO();
        initShaders();
    }

    SpriteBatch::~SpriteBatch()
    {
        for(auto glyph : m_Glyphs)
        {
            delete glyph;
        }
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
        clear();
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

    void SpriteBatch::draw(GLTexture a_Texture, const Rectangle& a_DestinationRectangle,
                           const Rectangle& a_UVRectangle, Color a_Color, float a_Depth)
    {
        auto glyph = new Glyph(a_Texture, a_DestinationRectangle, a_UVRectangle, a_Color, a_Depth);
        m_Glyphs.push_back(glyph);
    }

    void SpriteBatch::createVAO()
    {
        glGenVertexArrays(1, &m_VaoID);
        glBindVertexArray(m_VaoID);

        m_VBO.bind();

        for(auto i = 0; i < 3; ++i)
        {
            glEnableVertexAttribArray(i);
        }
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uvCoordinate)));

        glBindVertexArray(0);

        for(auto i = 0; i < 3; ++i)
        {
            glDisableVertexAttribArray(i);
        }
        m_VBO.unbind();
    }

    void SpriteBatch::sortGlyphs()
    {
        std::function<bool(Glyph*, Glyph*)> sortFunction;
        switch(m_SortMode)
        {
        case ESpriteSortMode::BackToFront:
            sortFunction = { [](Glyph* a_Value1, Glyph* a_Value2)
            {
                return a_Value1->depth < a_Value2->depth;
            } };
            break;
        case ESpriteSortMode::FrontToBack:
            sortFunction = { [](Glyph* a_Value1, Glyph* a_Value2)
            {
                return a_Value1->depth > a_Value2->depth;
            } };
            break;
        case ESpriteSortMode::Texture:
            sortFunction = { [](Glyph* a_Value1, Glyph* a_Value2)
            {
                return a_Value1->texture.getID() < a_Value2->texture.getID();
            } };
            break;
        }

        std::stable_sort(m_Glyphs.begin(), m_Glyphs.end(), sortFunction);
    }

    void SpriteBatch::renderBatches() const
    {
        glBindVertexArray(m_VaoID);
        glActiveTexture(GL_TEXTURE0);
        
        m_ShaderProgram.enable();
        auto textureLocation = m_ShaderProgram.getUniformLocation("sampler");
        glUniform1i(textureLocation, 0);

        auto cameraTransformLocation = m_ShaderProgram.getUniformLocation("cameraTransform");
        auto cameraTransform = m_Camera->getTransform();

        glUniformMatrix4fv(cameraTransformLocation, 1, GL_FALSE, &cameraTransform[0][0]);

        for(auto renderBatch : m_RenderBatches)
        {
            renderBatch.texture.bind();
            glDrawArrays(GL_TRIANGLES, renderBatch.offset, renderBatch.vertexCount);
        }

        m_ShaderProgram.disable();
    }

    void SpriteBatch::createRenderBatches()
    {
        const auto VerticesPerSprite = 6;

        std::vector<Vertex> vertices(m_Glyphs.size() * VerticesPerSprite);

        auto currentVertex = 0;
        auto currentOffset = 0;
        for(unsigned int i = 0; i < m_Glyphs.size(); ++i)
        {
            if(i == 0 || m_Glyphs[i]->texture.getID() != m_Glyphs[i - 1]->texture.getID())
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
        m_VBO.uploadData(vertices.data(), vertices.size());
    }
}