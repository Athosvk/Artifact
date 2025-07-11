#pragma once
#include <glm/glm.hpp>

namespace Artifact
{	
	/// <summary>
	/// Represents a rectangle for doing related calculations
	/// </summary>
	class Rectangle
    {
    private:		
		/// <summary>The lowest position of a vertex of the rectangle</summary>
		glm::vec2 m_MinPosition;
		/// <summary>The highest position of a vertex of the rectangle</summary>
        glm::vec2 m_MaxPosition;

    public:		
		/// <summary>Initializes a new instance of the <see cref="Rectangle"/> class.</summary>
		/// <param name="a_MinPosition">The minimum position.</param>
		/// <param name="a_MaxPosition">The maximum position.</param>
		Rectangle(const glm::vec2& a_MinPosition, const::glm::vec2& a_MaxPosition);
		
		/// <summary>Initializes a new instance of the <see cref="Rectangle"/> class.</summary>
		/// <param name="a_MinPosition">The minimum position.</param>
		/// <param name="a_Width">The width</param>
		/// <param name="a_Height">The height</param>
		Rectangle(const glm::vec2& a_MinPosition, float a_Width, float a_Height);
		
		/// <summary>Initializes a new instance of the <see cref="Rectangle"/> class.</summary>
		Rectangle() = default;
		
		/// <summary>Gets the width</summary>
		/// <returns>The width</returns>
		float getWidth() const;

		/// <summary>Gets the height</summary>
		/// <returns>The height</returns>
        float getHeight() const;

		/// <summary>Gets the radius</summary>
		/// <returns>The radius</returns>
        float getRadius() const;
		
		/// <summary>Gets the (center) position.</summary>
		/// <returns>The (center) position</returns>
		glm::vec2 getPosition() const;

		/// <summary>Gets the position of the topleft vertex</summary>
		/// <returns>The position of the topleft vertex</returns>
        glm::vec2 getTopLeft() const;
		
		/// <summary>Gets the position of the topright vertex</summary>
		/// <returns>The position of the topright vertex</returns>
		glm::vec2 getTopRight() const;
		
		/// <summary>Gets the position of the bottomleft vertex</summary>
		/// <returns>THe position of the bottomleft vertex</returns>
		glm::vec2 getBottomLeft() const;
		
		/// <summary>Gets the position of the bottomright vertex</summary>
		/// <returns>The position of the bottomright vertex</returns>
		glm::vec2 getBottomRight() const;
		
		/// <summary>Sets the width.</summary>
		/// <param name="a_Width">The new width</param>
		void setWidth(float a_Width);
		
		/// <summary>Sets the height.</summary>
		/// <param name="a_Height">The new height</param>
		void setHeight(float a_Height);
		
		/// <summary>Sets the minimum position.</summary>
		/// <param name="a_MinPosition">The new minimum position</param>
		void setMinPosition(glm::vec2 a_MinPosition);
		
		/// <summary>Sets the maximum position.</summary>
		/// <param name="a_MaxPosition">The new maximum position</param>
		void setMaxPosition(glm::vec2 a_MaxPosition);
		
		/// <summary>Sets the position.</summary>
		/// <param name="a_Position">The new position</param>
		void setPosition(glm::vec2 a_Position);
    };
}
