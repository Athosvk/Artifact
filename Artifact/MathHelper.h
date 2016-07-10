#pragma once
#include <glm/glm.hpp>

namespace Artifact
{	
	/// <summary>
	/// Provides functionality for generic math calculations
	/// </summary>
	class MathHelper
    {
    public:		
		/// <summary>Initializes a new instance of the <see cref="MathHelper"/> class.</summary>
		MathHelper() = delete;
		
		/// <summary>Finalizes an instance of the <see cref="MathHelper"/> class.</summary>
		~MathHelper() = delete;
		
		/// <summary>Clamps the specified value between the minimum and maximum	</summary>
		/// <param name="a_Value">The value to clamp</param>
		/// <param name="a_Min">The minimum value that will be returned if the value is lower than this value</param>
		/// <param name="a_Max">The maximum value that will be returned if the value is higher than this value</param>
		/// <returns>The value if it is between the specified boundaries, else the minimum or maximum</returns>
		static float clamp(float a_Value, float a_Min, float a_Max);
		
		/// <summary>Interpolates the value back and forth between the specified values</summary>
		/// <param name="a_Value">The value to send back and forth</param>
		/// <param name="a_Min">The minimum value</param>
		/// <param name="a_Max">The maximum value, before it will return to the minimum</param>
		/// <returns>The interpolated value</returns>
		static float pingPong(float a_Value, float a_Min, float a_Max);

		/// <summary>Returns the minimum of the two specified values</summary>
		/// <param name="a_Value1">The first value</param>
		/// <param name="a_Value2">The second value</param>
		/// <returns>The minimum of the two values</returns>
		template<typename T>
        static T min(T a_Value1, T a_Value2)
        {
            return a_Value1 < a_Value2 ? a_Value1 : a_Value2;
        }

		/// <summary>Returns the minimum of the two specified values</summary>
		/// <param name="a_Value1">The first value</param>
		/// <param name="a_Value2">The second value</param>
		/// <returns>The maximum of the two values</returns>
		template<typename T>
        static T max(T a_Value1, T a_Value2)
        {
            return a_Value1 > a_Value2 ? a_Value1 : a_Value2;
        }
		
		/// <summary>Rotates the specified vector around the specified origin</summary>
		/// <param name="a_Vector">The vector to rotate</param>
		/// <param name="a_Degrees">The amount to rotate the vector with</param>
		/// <param name="a_Origin">The origin to rotate the vector about</param>
		/// <returns>The rotated vector</returns>
		static glm::vec2 rotate(glm::vec2 a_Vector, float a_Degrees, glm::vec2 a_Origin);
		
		/// <summary>Creates a direction vector from an angle</summary>
		/// <param name="a_Degrees">The rotation of the vector in degrees</param>
		/// <returns>The resulting direction vector</returns>
		static glm::vec2 directionFromAngle(float a_Degrees);
				
		/// <summary>Gains the rotation of a vector from a normalized direction vector</summary>
		/// <param name="a_NormalizedDirection">The normalized direction vector</param>
		/// <returns>The rotation of the vector</returns>
		static float directionToAngle(glm::vec2 a_NormalizedDirection);
    };
}
