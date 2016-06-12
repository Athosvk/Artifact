#pragma once
#include <GL/glew.h>
#include <vector>

#include "../Rendering/Vertex.h"

namespace Artifact
{	
	/// <summary>
	/// Represents an OpenGL vertex buffer object that vertices can be stored in using
	/// the retrieved ID from the OpenGL API
	/// </summary>
	class VBO
    {
    private:		
		/// <summary>The identifier assigned by OpenGL for this buffer</summary>
		GLuint m_ID = 0;

    public:		
		/// <summary>Initializes a new instance of the <see cref="VBO"/> class.</summary>
		VBO();

		/// <summary>Finalizes an instance of the <see cref="VBO"/> class.</summary>
		~VBO();

		/// <summary>Uploads the vertex data</summary>
		/// <param name="a_Data">The data to upload</param>
		void uploadData(const std::vector<Vertex>& a_Data) const;
		
		/// <summary>Binds the VBO to make its vertex data part of the current state</summary>
		void bind() const;
		
		/// <summary>Sets the VBO state to its default, unbinding this VBO</summary>
		void unbind() const;
    };
}
