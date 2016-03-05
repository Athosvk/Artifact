#pragma once
#include <GL/glew.h>

namespace Artifact
{
    class GLSLProgram
    {
    private:
        int m_AttributeCount = 0;
        GLuint m_ProgramID = glCreateProgram();
        GLuint m_VertexShaderID = 0;
        GLuint m_FragmentShaderID = 0;
        std::string m_VertexShader;
        std::string m_FragmentShader;

    public:
        GLSLProgram(const std::string& a_VertexShaderPath, const std::string& a_FragmentShaderPath);
        ~GLSLProgram();

        void createAndCompileShaders();
        void linkShaders() const;
        void addAttribute(const std::string& a_AttributeName);

        void enable() const;
        void disable() const;
        GLuint getUniformLocation(const std::string& a_UniformName) const;

    private:
        void createVertexShader();
        void createFragmentShader();
        void loadAndCompileShader(GLuint a_ShaderID, const std::string& a_FilePath) const;

        void printShaderInfoLog(GLuint a_ShaderID) const;
        void printProgramInfoLog(GLuint a_ProgramID) const;
    };
}

