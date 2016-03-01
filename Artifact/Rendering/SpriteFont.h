/* 
    This is a modified version of the SpriteFont class from the
    Seed Of Andromeda source code.
    Use it for any of your projects, commercial or otherwise,
    free of charge, but do not remove this disclaimer.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS
    ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
    EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
    INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
    RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
    ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
    OF THIS SOFTWARE.

    November 28 2014
    Original Author: Cristian Zaloj
    Modified By: Benjamin Arnold
*/

#pragma once

#include <TTF/sdl_ttf.h>
#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <memory>

#include "Vertex.h"
#include "../Color.h"
#include "../GL/GLTexture.h"
#include "../Rectangle.h"

namespace Artifact {

    class SpriteBatch;

    struct CharGlyph 
    {
    public:
        char character;
        Rectangle uvRect;
        glm::vec2 size;
    };

#define FIRST_PRINTABLE_CHAR ((char)32)
#define LAST_PRINTABLE_CHAR ((char)126)

    /// For text justification
    enum class EJustification 
    {
        Left, Middle, Right
    };

    class SpriteFont {
    private:
        int _regStart, _regLength;
        CharGlyph* _glyphs;
        int _fontHeight;
        std::unique_ptr<GLTexture> m_Texture = nullptr;
        unsigned int _texID = 0;
    public:
        SpriteFont(const char* font, int size, char cs, char ce);
        SpriteFont(const char* font, int size) :
            SpriteFont(font, size, FIRST_PRINTABLE_CHAR, LAST_PRINTABLE_CHAR) {
        }
        /// Destroys the font resources
        void dispose();

        int getFontHeight() const;

        /// Measures the dimensions of the text
        glm::vec2 measure(const char* s);

        /// Draws using a spritebatch
        void draw(SpriteBatch& batch, const char* s, glm::vec2 position, glm::vec2 scaling, 
                  float depth, Color tint, EJustification just = EJustification::Left);
    private:
        static std::vector<int>* createRows(glm::ivec4* rects, int rectsLength, int r, int padding, int& w);
    };
}