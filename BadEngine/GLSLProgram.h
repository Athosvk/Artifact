#pragma once
#include <GL/glew.h>

namespace BadEngine
{
    class GLSLProgram
    {
    private:
        int m_AttributeCount;
        GLuint m_ProgramID;
        GLuint m_VertexShaderID;
        GLuint m_FragmentShaderID;
        std::string m_VertexShader;
        std::string m_FragmentShader;

    public:
        GLSLProgram(const std::string& a_VertexShaderPath, const std::string& a_FragmentShaderPath);

        void createAndCompileShaders();
        void linkShaders() const;
        void addAttribute(const std::string& a_AttributeName);

        void setAsCurrent() const;
        void resetCurrent() const;
        GLuint getUniformLocation(const std::string& a_UniformName) const;

    private:
        void createVertexShader();
        void createFragmentShader();
        void loadAndCompileShader(GLuint a_ShaderID, const std::string& a_FilePath) const;

        void printShaderInfoLog(GLuint a_ShaderID) const;
        void printProgramInfoLog(GLuint a_ProgramID) const;
    };
}

