#include "SpriteBatch.h"
#include <algorithm>
#include <functional>

namespace BadEngine
{
    SpriteBatch::SpriteBatch()
    {
        createVAO();
    }

    SpriteBatch::~SpriteBatch()
    {
    }

    void SpriteBatch::begin(ESpriteSortMode a_SpriteSortMode)
    {
        m_SortMode = a_SpriteSortMode;
    }

    void SpriteBatch::end()
    {
        sortGlyphs();
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
    }

    void SpriteBatch::sortGlyphs()
    {
        std::function<bool()> sortFunction;
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
}