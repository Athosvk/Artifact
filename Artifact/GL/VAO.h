#pragma once
#include <GL/glew.h>

namespace Artifact
{	
	/// <summary>
	/// Represents a vertex array object, for combining attributes
	/// </summary>
	class VAO
    {
    private:
		/// <summary>The ID of the vertex array object</summary>
		GLuint m_ID = 0;

    public:
		/// <summary>Initializes a new instance of the <see cref="VAO"/> class.</summary>
		VAO();

		/// <summary>Finalizes an instance of the <see cref="VAO"/> class.</summary>
		~VAO();
		
		/// <summary>Binds the VAO for drawing</summary>
		void bind() const;
		
		/// <summary>Resets the VAO bind state to the default</summary>
		void unbind() const;
    };
}
