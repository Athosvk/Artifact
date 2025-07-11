#pragma once
#include <GL/glew.h>
#include <string>

namespace Artifact
{	
	/// <summary>
	/// Represents a combination of a fragment and vertex shader that are associated with OpenGL
	/// </summary>
	class GLSLProgram
    {
    private:		
		/// <summary>The vertex attributes discovered by the program for the shader</summary>
		int m_AttributeCount = 0;		
		/// <summary>The id of the program assigned by the OpenGL interface</summary>
		GLuint m_ProgramID = glCreateProgram();		
		/// <summary>The id of the vertex shader associated with this program</summary>
		GLuint m_VertexShaderID = 0;		
		/// <summary>The id of the fragment shader associated with this program</summary>
		GLuint m_FragmentShaderID = 0;		
		/// <summary>The name of the vertex shader used for this program</summary>
		std::string m_VertexShader;		
		/// <summary>The name of the fragment shader used for this program</summary>
		std::string m_FragmentShader;

    public:		
		/// <summary>Initializes a new instance of the <see cref="GLSLProgram"/> class.</summary>
		/// <param name="a_VertexShaderPath">The path to the vertex shader to use</param>
		/// <param name="a_FragmentShaderPath">The path to the fragment shader to use</param>
		GLSLProgram(const std::string& a_VertexShaderPath, const std::string& a_FragmentShaderPath);
		
		/// <summary>Finalizes an instance of the <see cref="GLSLProgram"/> class.</summary>
		~GLSLProgram();
		
		/// <summary>Creates the and compiles the associated shaders</summary>
		void createAndCompileShaders();
		
		/// <summary>Links the shaders to the program</summary>
		void linkShaders() const;
		
		/// <summary>Adds an attribute based on its name</summary>
		/// <param name="a_AttributeName">Name of the attribute.</param>
		void addAttribute(const std::string& a_AttributeName);
		
		/// <summary>Sets the GLSL program as the active one</summary>
		void enable() const;

		/// <summary>Renders the state of the active GLSL program, making this one no longer apply to objects drawn</summary>
		void disable() const;
		
		/// <summary>Gets the ID of the specified unifrom variable</summary>
		/// <param name="a_UniformName">Name of the uniform</param>
		/// <returns>The uniform's index</returns>
		GLuint getUniformLocation(const std::string& a_UniformName) const;

    private:
		/// <summary>Creates the vertex shader to be associated with the GLSLProgram</summary>
		void createVertexShader();
		
		/// <summary>Creates the fragment shader to be associated with the GLSLProgram</summary>
		void createFragmentShader();
		
		/// <summary>Loads the and compile shader.</summary>
		/// <param name="a_ShaderID">The ID of the shader to load and compile</param>
		/// <param name="a_FilePath">The path to the shader</param>
		void loadAndCompileShader(GLuint a_ShaderID, const std::string& a_FilePath) const;
		
		/// <summary>Prints the information about the specified shader, regarding the success of the compilation</summary>
		/// <param name="a_ShaderID">The identifier of the shader</param>
		void printShaderInfoLog(GLuint a_ShaderID) const;
		
		/// <summary>Prints the information about the specified program, regarding the success of the compilation</summary>
		/// <param name="a_ProgramID">The a_ program identifier.</param>
		void printProgramInfoLog(GLuint a_ProgramID) const;
    };
}

