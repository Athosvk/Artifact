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
	/// <summary>
	/// Determines the type of sprite sort mode, depicting how efficient and how the sprites are rendered
	/// </summary>
	enum class ESpriteSortMode
    {		
		/// <summary>Sorts the sprites based on their depth, front first back last</summary>
		FrontToBack,		
		/// <summary>Sorts the sprites based on their depth, front last back first</summary>
		BackToFront,		
		/// <summary> Sorts the sprites based on their texture, grouping them together based on it </summary>
		Texture
    };
	
	/// <summary>
	/// Batches sprites together and renders them to the screen
	/// </summary>
	class SpriteBatch
    {
    private:		
		/// <summary>
		/// Represents a single batch of the vertices of sprites that use the same texture
		/// </summary>
		class RenderBatch
        {
        public:			
			/// <summary>The texture used by the sprites in this batch</summary>
			const GLTexture* Texture;			
			/// <summary>The amount of vertex indices used by this batch of sprites</summary>
			GLuint IndexCount;			
			/// <summary>The offset into the index array</summary>
			GLuint Offset;

        public:			
			/// <summary>Initializes a new instance of the <see cref="RenderBatch"/> class.</summary>
			/// <param name="a_Texture">The texture used by the sprites in this batch</param>
			/// <param name="a_Offset">The amount of vertex indices used by this batch of sprites</param>
			/// <param name="a_IndexCount">The offset into the indices array</param>
			RenderBatch(const GLTexture* a_Texture, GLuint a_Offset, GLuint a_IndexCount = 0);
        };
		
		/// <summary>
		/// Represents a single sprite
		/// </summary>
		class Glyph
        {
        public:			
			/// <summary>The texture used by the sprite</summary>
			const GLTexture* Texture;			
			/// <summary>The depth of the sprite, also known as its z position</summary>
			float Depth;			
			/// <summary>The bottom left vertex of the sprite</summary>
			Vertex BottomLeft;			
			/// <summary>The bottom right vertex of the sprite</summary>
			Vertex BottomRight;			
			/// <summary>The top right vertex of the sprite</summary>
			Vertex TopRight;			
			/// <summary>The top left vertex of the sprite</summary>
			Vertex TopLeft;

        public:			
			/// <summary>Initializes a new instance of the <see cref="Glyph"/> class.</summary>
			/// <param name="a_Texture">The texture to be used by the sprite</param>
			/// <param name="a_DestinationRectangle">The destination rectangle of the sprite, where it should be placed in</param>
			/// <param name="a_Color">The color of the sprite</param>
			/// <param name="a_UVRectangle">The uv rectangle of the sprite</param>
			/// <param name="a_Depth">The depth, also known as its z coordinate, of the sprite</param>
			Glyph(const GLTexture* a_Texture, const Rectangle& a_DestinationRectangle, Color a_Color,
                  const Rectangle& a_UVRectangle, float a_Depth);
			
			/// <summary>Initializes a new instance of the <see cref="Glyph"/> class.</summary>
			/// <param name="a_Texture">The texture to be used by the sprite</param>
			/// <param name="a_DestinationRectangle">The destination rectangle of the sprite, where it should be placed in</param>
			/// <param name="a_Rotation">The rotation of the sprite</param>
			/// <param name="a_Origin">The origin/pivot of the sprite, used for it's rotation</param>
			/// <param name="a_Color">Color of the sprite</param>
			/// <param name="a_UVRectangle">The uv rectangle of the sprite</param>
			/// <param name="a_Depth">The depth, also known as its z coordinate, of the sprite</param>
			Glyph(const GLTexture* a_Texture, const Rectangle& a_DestinationRectangle, float a_Rotation,
                  glm::vec2 a_Origin, Color a_Color, const Rectangle& a_UVRectangle, float a_Depth);
        };

		/// <summary>The default vertex shader used for rendering sprites</summary>
        static const std::string SpriteBatch::s_DefaultVertexShader;
		/// <summary>The default fragment shader used for rendering sprites</summary>
		static const std::string SpriteBatch::s_DefaultFragmentShader;
		
		/// <summary>The vertex array object used for saving the state used to set up the sprite input</summary>
		VAO m_VAO;		
		/// <summary>The vertex buffer object used for storing the vertices related to the sprites rendered</summary>
		VBO m_VBO;		
		/// <summary>The index buffer object used for storing the vertices related to indicies of the vertices used by the sprites</summary>
		IBO m_IBO;		
		/// <summary>The glyphs representing the sprites for which a draw command has been issued during this frame</summary>
		std::vector<Glyph> m_Glyphs;		
		/// <summary>The render batches, representing the batches of sprites by texture that are to be rendered</summary>
		std::vector<RenderBatch> m_RenderBatches;		
		/// <summary>The sprite sort mode used during this frame</summary>
		ESpriteSortMode m_SortMode = ESpriteSortMode::BackToFront;		
		/// <summary>The shader program used for rendering the sprites</summary>
		GLSLProgram m_ShaderProgram;		
		/// <summary>The view projection matrix used for rendering the sprites</summary>
		glm::mat4 m_ViewProjectionMatrix;

    public:		
		/// <summary>Initializes a new instance of the <see cref="SpriteBatch"/> class.</summary>
		SpriteBatch();
		
		/// <summary>Begins the rendering phase, readying it for issueing draw commands</summary>
		/// <param name="a_ViewProjectionMatrix">The view projection matrix.</param>
		/// <param name="a_SpriteSortMode">The sort mode used to sort the sprites before they are rendered</param>
		void begin(glm::mat4 a_ViewProjectionMatrix, ESpriteSortMode a_SpriteSortMode = ESpriteSortMode::BackToFront);
		
		/// <summary>Draws a sprite based on the specified parameters</summary>
		/// <param name="a_Texture">The texture to use for the sprite</param>
		/// <param name="a_DestinationRectangle">The destination rectangel</param>
		/// <param name="a_Color">The color</param>
		/// <param name="a_UVRectangle">The uv rectangle, specifying how the texture should map to the sprite</param>
		/// <param name="a_Depth">The depth of the sprite</param>
		void draw(const GLTexture* a_Texture, const Rectangle& a_DestinationRectangle, Color a_Color = Color::White,
                  const Rectangle& a_UVRectangle = Rectangle(glm::vec2(0, 0), 1, 1), float a_Depth = 0);
		
		/// <summary>Draws a sprite based on the specified parameters</summary>
		/// <param name="a_Texture">The texture to use</param>
		/// <param name="a_Position">The position of the sprite in the world</param>
		/// <param name="a_Color">The color</param>
		/// <param name="a_UVRectangle">The uv rectangle, specifying how the texture should map to the sprite</param>
		/// <param name="a_Depth">The depth</param>
		void draw(const GLTexture* a_Texture, glm::vec2 a_Position, Color a_Color = Color::White,
                  const Rectangle& a_UVRectangle = Rectangle(glm::vec2(0, 0), 1, 1), float a_Depth = 0);
		
		/// <summary>Draws a sprite based on the specified parameters</summary>
		/// <param name="a_Texture">The texture to use</param>
		/// <param name="a_DestinationRectangle">The destination rectangle to draw the sprite in</param>
		/// <param name="a_Rotation">The rotation</param>
		/// <param name="a_Origin">The origin/pivot of the sprite, to rotate about</param>
		/// <param name="a_Color">The color</param>
		/// <param name="a_UVRectangle">The uv rectangle, specifying how the texture should map to the sprite</param>
		/// <param name="a_Depth">The depth</param>
		void draw(const GLTexture* a_Texture, const Rectangle& a_DestinationRectangle, float a_Rotation,
                  glm::vec2 a_Origin, Color a_Color = Color::White,
                  const Rectangle& a_UVRectangle = Rectangle(glm::vec2(0, 0), 1, 1), float a_Depth = 0);
		
		/// <summary>Draws a sprite based on the specified parameters</summary>
		/// <param name="a_Texture">The texture to use</param>
		/// <param name="a_Position">The position to draw the sprite at</param>
		/// <param name="a_Rotation">The rotation</param>
		/// <param name="a_Origin">The orgin of the sprite's rotation</param>
		/// <param name="a_Color">The color</param>
		/// <param name="a_UVRectangle">The uv rectangle, specifying how the texture should map to the sprite</param>
		/// <param name="a_Depth">The depth</param>
		void draw(const GLTexture* a_Texture, glm::vec2 a_Position, float a_Rotation,
                  glm::vec2 a_Origin, Color a_Color = Color::White,
                  const Rectangle& a_UVRectangle = Rectangle(glm::vec2(0, 0), 1, 1), float a_Depth = 0);
		
		/// <summary>Ends the rendering phase, submitting the needed draw calls to render the sprites</summary>
		void end();

    private:		
		/// <summary>Binds the uniforms needed to draw the sprites</summary>
		void bindUniforms() const;
		
		/// <summary>Sends the draw calls for each render batch</summary>
		void renderBatches() const;
		
		/// <summary>Constructs the vertex array object</summary>
		void constructVAO() const;
		
		/// <summary>Constructs the index buffer object</summary>
		void constructIBO();
		
		/// <summary>Constructs the vertex buffer object</summary>
		void constructVBO() const;
		
		/// <summary>Sorts the glyphs, waiting to be drawn, based on the sort mode</summary>
		void sortGlyphs();
		
		/// <summary>Creates the render batches needed to draw all the glyphs</summary>
		void createRenderBatches();
		
		/// <summary>Initializes the shaders </summary>
		void initShaders();
				
		/// <summary>Clears the previous state of the objects waiting to be drawn</summary>
		void clear();
    };
}