#pragma once
#include <string>

#include "SpriteFont.h"
#include "../Core/Component.h"

namespace Artifact
{	
	/// <summary>
	/// Represents text visuals for UI rendering
	/// </summary>
	/// <seealso cref="Component" />
	class TextComponent : public Component
    {
    public:		
		/// <summary>The font</summary>
		SpriteFont* Font;		
		/// <summary>The text to display</summary>
		std::string Text;		
		/// <summary>The scaling/size factor</summary>
		float Scaling = 1.0f;		
		/// <summary>The depth</summary>
		float Depth = 0.0f;		
		/// <summary>The color</summary>
		Color Color = Color::White;		
		/// <summary>The justification/pivot</summary>
		EJustification Justification = EJustification::Middle;

    public:		
		/// <summary>Initializes a new instance of the <see cref="TextComponent"/> class.</summary>
		/// <param name="a_Entity">The entity to which it is attached</param>
		TextComponent(GameObject a_Entity);
    };
}
