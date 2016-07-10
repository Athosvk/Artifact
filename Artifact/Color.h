#pragma once
#include <stdint.h>

namespace Artifact
{	
	/// <summary>
	/// Represents an RGBA float color
	/// </summary>
	struct Color
    {
    public:		
		/// <summary>
		/// The red component
		/// </summary>
		float R = 0.0f;
		/// <summary>
		/// The green component
		/// </summary>
        float G = 0.0f;
		/// <summary>
		/// The blue component
		/// </summary>
        float B = 0.0f;
		/// <summary>
		/// The alpha component
		/// </summary>
        float A = 0.0f;

		/// <summary>
		/// Represents a color instance that matches the color white
		/// </summary>
		static const Color White;
		/// <summary>
		/// Represents a color instance that matches the color black
		/// </summary>
        static const Color Black;
		/// <summary>
		/// Represents a color instance that matches the color red
		/// </summary>
        static const Color Red;
		/// <summary>
		/// Represents a color instance that matches the color blue
		/// </summary>
        static const Color Blue;
		/// <summary>
		/// Represents a color instance that matches the color green
		/// </summary>
		static const Color Green;
		/// <summary>
		/// Represents a color instance that matches the color yellow
		/// </summary>
		static const Color Yellow;
		/// <summary>
		/// Represents a color instance that matches the color gray
		/// </summary>
		static const Color Gray;
		/// <summary>
		/// Represents a color instance that matches the color magenta
		/// </summary>
		static const Color Magenta;
		/// <summary>
		/// Represents a color instance that matches the color cyan
		/// </summary>
		static const Color Cyan;

    public:		
		/// <summary>Initializes a new instance of the <see cref="Color"/> struct.</summary>
		/// <param name="a_RedValue">The red component</param>
		/// <param name="a_GreenValue">The green component</param>
		/// <param name="a_BlueValue">The blue component</param>
		/// <param name="a_AlphaValue">The alpha/opacity component</param>
		Color(float a_RedValue, float a_GreenValue, float a_BlueValue, float a_AlphaValue = 1);
		Color() = default;
        		
		/// <summary>Creates a color instance from an RGBA integer</summary>
		/// <param name="a_Value">The value to create the color instance from</param>
		/// <returns>The created color instance</returns>
		static Color createFromRGBAValue(uint64_t a_Value);
    };
}