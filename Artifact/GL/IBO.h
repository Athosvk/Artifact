#pragma once
#include <GL/glew.h>
#include <vector>

namespace Artifact
{	
	/// <summary>
	/// Specifies the way the buffer will be used
	/// </summary>
	enum class EBufferUsage
    {		
		/// <summary>The buffer is dynamic and will be updated at regular intervals; write many, read write once</summary>
		Dynamic = GL_DYNAMIC_DRAW,		
		/// <summary>The buffer is a stream and will be updated less regularly, but read out often; write many, read many for every write</summary>
		Stream = GL_STREAM_DRAW,        
		/// <summary>The buffer is static and will not be updated; write once, read many</summary>
		Static = GL_STATIC_DRAW
    };
	
	/// <summary>
	/// Provides an interface to a GPU index buffer object
	/// </summary>
	class IBO
    {
    private:
		/// <summary>The ID of the index buffer, retrieved from OpenGL</summary>
		GLuint m_ID = 0;
		/// <summary>The usage of this buffer</summary>
		EBufferUsage m_Usage;		
		/// <summary>The data that is mirrored on the GPU </summary>
		std::vector<GLuint> m_Data;

    public:		
		/// <summary>Initializes a new instance of the <see cref="IBO"/> class.</summary>
		/// <param name="a_BufferUsage">The buffer usage </param>
		/// <param name="a_InitialData">The initial data of the buffer</param>
		IBO(EBufferUsage a_BufferUsage, const std::vector<GLuint>& a_InitialData = std::vector<GLuint>());
        		
		/// <summary>Finalizes an instance of the <see cref="IBO"/> class.</summary>
		~IBO();
		
		/// <summary>Binds the IBO to OpenGL for drawing</summary>
		void bind() const;
		
		/// <summary>Resets the IBO state to the default</summary>
		void unbind() const;
		
		/// <summary>Draws the specified amount of indices from the buffer</summary>
		/// <param name="a_IndexCount">The amount of indices to draw</param>
		/// <param name="a_Offset">The offset to start drawing from</param>
		void draw(GLuint a_IndexCount, GLuint a_Offset) const;
		
		/// <summary>Sets the IBO data to draw</summary>
		/// <param name="a_Data">The new data</param>
		void setData(const std::vector<GLuint>& a_Data);

    private:		
		/// <summary>Uploads the data to the GPU</summary>
		void uploadData() const;
    };
}
