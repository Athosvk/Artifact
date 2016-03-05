#include <fstream>
#include <vector>

#include "GLSLProgram.h"
#include "..\ErrorHandler.h"
#include "GL.h"
#include "..\IO\IOManager.h"

namespace Artifact
{
    GLSLProgram::GLSLProgram(const std::string& a_VertexShaderPath, const std::string& a_FragmentShaderPath) :
        m_VertexShader(a_VertexShaderPath),
        m_FragmentShader(a_FragmentShaderPath)
    {
    }

    GLSLProgram::~GLSLProgram()
    {
        glDeleteProgram(m_ProgramID);
    }

    void GLSLProgram::createAndCompileShaders()
    {
        createVertexShader();
        createFragmentShader();

        loadAndCompileShader(m_VertexShaderID, m_VertexShader);
        loadAndCompileShader(m_FragmentShaderID, m_FragmentShader);
    }

    GLuint GLSLProgram::getUniformLocation(const std::string& a_UniformName) const
    {
        auto location = glGetUniformLocation(m_ProgramID, a_UniformName.c_str());
        if(location == GL_INVALID_INDEX)
        {
            throwFatalError("Uniform " + a_UniformName + " not found in shader");
        }
        return location;
    }

    void GLSLProgram::createVertexShader()
    {
        m_VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        if(m_VertexShaderID == 0)
        {
            throwFatalError("Failed to initialise vertex shader: " + GL::getErrorString());
        }
    }

    void GLSLProgram::createFragmentShader()
    {
        m_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        if(m_FragmentShaderID == 0)
        {
            throwFatalError("Failed to initialise fragment shader " + GL::getErrorString());
        }
    }

    void GLSLProgram::loadAndCompileShader(GLuint a_ShaderID, const std::string& a_FilePath) const
    {
        std::vector<char> shaderContents;
        IOManager::readText(shaderContents, a_FilePath);
        auto contentBuffer = shaderContents.data();

        glShaderSource(a_ShaderID, 1, &contentBuffer, nullptr);
        glCompileShader(a_ShaderID);

        auto compiled = 0;
        glGetShaderiv(a_ShaderID, GL_COMPILE_STATUS, &compiled);

        if(compiled == GL_FALSE)
        {
            printShaderInfoLog(a_ShaderID);
            glDeleteShader(a_ShaderID);
            throwFatalError("Failed to compile shader " + a_FilePath);
        }
    }
    
    void GLSLProgram::linkShaders() const
    {
        glAttachShader(m_ProgramID, m_VertexShaderID);
        glAttachShader(m_ProgramID, m_FragmentShaderID);
        glLinkProgram(m_ProgramID);

        auto linked = GL_FALSE;
        glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &linked);

        if(linked == GL_FALSE)
        {
            printProgramInfoLog(m_ProgramID);

            glDeleteProgram(m_ProgramID);
            glDeleteShader(m_VertexShaderID);
            glDeleteShader(m_FragmentShaderID);
            throwFatalError("Failed to link program and shaders");
        }
        glDetachShader(m_ProgramID, m_VertexShaderID);
        glDetachShader(m_ProgramID, m_FragmentShaderID);
        glDeleteShader(m_VertexShaderID);
        glDeleteShader(m_FragmentShaderID);
    }

    void GLSLProgram::addAttribute(const std::string& a_AttributeName)
    {
        glBindAttribLocation(m_ProgramID, m_AttributeCount++, a_AttributeName.c_str());
    }

    void GLSLProgram::printShaderInfoLog(GLuint a_ShaderID) const
    {
        auto maxLength = 0;
        glGetShaderiv(a_ShaderID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> log(maxLength);
        glGetShaderInfoLog(a_ShaderID, maxLength, &maxLength, &log[0]);
        std::printf("%s\n", &(log[0]));
    }

    void GLSLProgram::printProgramInfoLog(GLuint a_ProgramID) const
    {
        auto maxLength = 0;
        glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> errorLog(maxLength);
        glGetProgramInfoLog(a_ProgramID, maxLength, &maxLength, &errorLog[0]);
        std::printf("%s\n", &(errorLog[0]));
    }

    void GLSLProgram::enable() const
    {
        glUseProgram(m_ProgramID);
    }

    void GLSLProgram::disable() const
    {
        glUseProgram(0);
    }
}