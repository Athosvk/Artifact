#pragma once
#include <GL/glew.h>
#include <vector>

namespace Artifact
{	
	/// <summary>
	/// Represents a client interface to a GPU allocated texture initialized with the OpenGL interface
	/// </summary>
	class GLTexture
    {
    private:		
		/// <summary>The identifier of the texture</summary>
		GLuint m_ID = 0;		
		/// <summary>The width of the texture</summary>
		float m_Width = 0.0f;		
		/// <summary>The height of the texture</summary>
		float m_Height = 0.0f;

    public:		
		/// <summary>Initializes a new instance of the <see cref="GLTexture"/> class.</summary>
		/// <param name="a_Width">Width of the texture</param>
		/// <param name="a_Height">Height of the texture</param>
		GLTexture(float a_Width, float a_Height);
		
		/// <summary>Initializes a new instance of the <see cref="GLTexture"/> class.</summary>
		/// <param name="a_ID">The a_ identifier.</param>
		explicit GLTexture(GLuint a_ID);
		
		/// <summary>Finalizes an instance of the <see cref="GLTexture"/> class.</summary>
		~GLTexture();
		
		/// <summary>Compares the GLTexture with the other texture to see if it is considered larger than it</summary>
		/// <param name="a_Other">The other GLTexture to compare against</param>
		/// <returns>Whether the instance is bigger than the provided GLTexture</returns>
		bool operator >(const GLTexture& a_Other) const;
		
		/// <summary>Compares the GLTExture with the other texture to see if it is considered smaller than it</summary>
		/// <param name="a_Other">The other GLTexture to compare against</param>
		/// <returns>Whether the instance is smaller than the provided GLTexture</returns>
		bool operator <(const GLTexture& a_Other) const;
		
		/// <summary>Compares the GLTexture with the other texture to see if it is considered larger or equal to it</summary>
		/// <param name="a_Other">The other GLTexture to compare against</param>
		/// <returns>Whether the instance is larger than or equal to the provided GLTexture</returns>
		bool operator >=(const GLTexture& a_Other) const;

		/// <summary>Compares the GLTexture with the other texture to see if it is considered smaller or equal to it</summary>
		/// <param name="a_Other">The other GLTexture to compare against</param>
		/// <returns>Whether the instance is smaller than or equal to the provided GLTexture</returns>
        bool operator <=(const GLTexture& a_Other) const;

		/// <summary>Compares the GLTexture with the other texture to see if it is considered equal to it</summary>
		/// <param name="a_Other">The other GLTexture to compare against</param>
		/// <returns>Whether the instance is equal to the provided GLTexture</returns>
        bool operator ==(const GLTexture& a_Other) const;

		/// <summary>Compares the GLTexture with the other texture to see if it is considered unequal</summary>
		/// <param name="a_Other">The other GLTexture to compare against</param>
		/// <returns>Whether the instance is not equal to the provided GLTexture</returns>
        bool operator !=(const GLTexture& a_Other) const;
		
		/// <summary>Binds this texture as the current one, so it can be used for rendering</summary>
		void bind() const;
		
		/// <summary>Unbinds the texture from the OpenGL interface</summary>
		void unbind() const;
		
		/// <summary>Uploads the given texture data to the GPU</summary>
		/// <param name="a_Data">The data to upload</param>
		void uploadData(const std::vector<unsigned char>& a_Data) const;
		
		/// <summary>Gets the height stored in the texture data</summary>
		/// <returns>The height of the texture</returns>
		float getHeight() const;
		
		/// <summary>Gets the width stored in the texture data</summary>
		/// <returns>The width of the texture</returns>
		float getWidth() const;
    };
}