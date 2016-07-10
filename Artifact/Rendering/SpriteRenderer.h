#pragma once
#include "../Core/Component.h"
#include "../GL/GLTexture.h"
#include "../Color.h"
#include "../Rectangle.h"

namespace Artifact
{	
	/// <summary>
	/// Species sprite information to render a sprite associated with the entity to the screen
	/// </summary>
	/// <seealso cref="Component" />
	class SpriteRenderer : public Component
    {
    private:		
		/// <summary>The texture to use for drawing the sprite</summary>
		GLTexture* Texture;

    public:		
		/// <summary>The width</summary>
		float Width;		
		/// <summary>The height</summary>
		float Height;		
		/// <summary>The color</summary>
		Artifact::Color Color = Artifact::Color::White;		
		/// <summary>The uv rectangle to use for mapping the UV coordinates</summary>
		Artifact::Rectangle UVRectangle = Artifact::Rectangle(glm::vec2(0.0f, 0.0f), 1.0f, 1.0f);		
		/// <summary>The depth</summary>
		float Depth = 0.0f;		
		/// <summary>The pivot of the sprite, which it will rotate about</summary>
		glm::vec2 Pivot = glm::vec2(0.5f, 0.5f);

    public:		
		/// <summary>Initializes a new instance of the <see cref="SpriteRenderer"/> class.</summary>
		/// <param name="a_GameObject">The game object to which the sprite is attached</param>
		SpriteRenderer(GameObject a_GameObject);
		
		/// <summary>Gets the texture used for the rendering of the sprite</summary>
		/// <returns>The texture used</returns>
		GLTexture* getTexture() const;
		
		/// <summary>Sets the texture</summary>
		/// <param name="a_Texture">The texture to use for the sprite</param>
		void setTexture(GLTexture* a_Texture);
    };
}
