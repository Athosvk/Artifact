#pragma once
#include <glm/glm.hpp>

#include "..\Color.h" 

namespace Artifact
{	
	/// <summary>
	/// Represents a single vertex of a sprite/model that is used for rendering
	/// </summary>
	struct Vertex
    {
    public:		
		/// <summary>The position</summary>
		glm::vec2 position = glm::vec2(0.0f, 0.0f);		
		/// <summary>The color</summary>
		Color color;		
		/// <summary>The uv coordinate</summary>
		glm::vec2 uvCoordinate = glm::vec2(0.0f, 0.0f);
		
		/// <summary>Initializes a new instance of the <see cref="Vertex"/> struct.</summary>
		/// <param name="a_Position">The position.</param>
		/// <param name="a_Color">The color</param>
		/// <param name="a_UVCoordinate">The uv coordinate.</param>
		Vertex(glm::vec2 a_Position, Color a_Color, glm::vec2 a_UVCoordinate)
            : position(a_Position), color(a_Color), uvCoordinate(a_UVCoordinate)
        {
            
        }
		
		/// <summary>Initializes a new instance of the <see cref="Vertex"/> struct.</summary>
		Vertex() = default;
    };
}