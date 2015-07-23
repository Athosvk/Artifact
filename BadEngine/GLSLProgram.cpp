#include <fstream>
#include <vector>
#include <iostream>

#include "GLSLProgram.h"
#include "ErrorHandler.h"

namespace BadEngine
{
    GLSLProgram::GLSLProgram(const std::string& a_VertexShaderPath, const std::string& a_FragmentShaderPath) :
        m_AttributeCount(0),
        m_ProgramID(0),
        m_VertexShaderID(0),
        m_FragmentShaderID(0)
    {
        m_VertexShader = a_VertexShaderPath;
        m_FragmentShader = a_FragmentShaderPath;
    }

    void GLSLProgram::createAndCompileShaders()
    {
        m_ProgramID = glCreateProgram();
        createVertexShader();
        createFragmentShader();

        loadAndCompileShader(m_VertexShaderID, m_VertexShader);
        loadAndCompileShader(m_FragmentShaderID, m_FragmentShader);
    }

    GLuint GLSLProgram::getUniformLocation(const std::string& a_UniformName)
    {
        GLint location = glGetUniformLocation(m_ProgramID, a_UniformName.c_str());
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
            throwFatalError("Failed to initialise vertex shader");
        }
    }

    void GLSLProgram::createFragmentShader()
    {
        m_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        if(m_FragmentShaderID == 0)
        {
            throwFatalError("Failed to initialise fragment shader");
        }
    }

    void GLSLProgram::loadAndCompileShader(GLuint a_ShaderID, const std::string& a_FilePath)
    {
        std::ifstream shaderFile(a_FilePath);
        if(shaderFile.fail())
        {
            perror(a_FilePath.c_str());
            throwFatalError("Failed to open " + a_FilePath);
        }

        std::string fileContents = "";
        std::string line;

        while(std::getline(shaderFile, line))
        {
            fileContents += line + "\n";
        }

        shaderFile.close();

        const char* contents = fileContents.c_str();
        glShaderSource(a_ShaderID, 1, &contents, nullptr);

        glCompileShader(a_ShaderID);

        GLint compiled = 0;
        glGetShaderiv(a_ShaderID, GL_COMPILE_STATUS, &compiled);

        if(compiled == GL_FALSE)
        {
            printShaderInfoLog(a_ShaderID);
            glDeleteShader(a_ShaderID);
            throwFatalError("Failed to compile shader " + a_FilePath);
        }
    }

    void GLSLProgram::linkShaders()
    {
        glAttachShader(m_ProgramID, m_VertexShaderID);
        glAttachShader(m_ProgramID, m_FragmentShaderID);
        glLinkProgram(m_ProgramID);

        GLint linked = 0;
        glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &((int) linked));

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

    void GLSLProgram::printShaderInfoLog(GLuint a_ShaderID)
    {
        GLint maxLength = 0;
        glGetShaderiv(a_ShaderID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> log(maxLength);
        glGetShaderInfoLog(a_ShaderID, maxLength, &maxLength, &log[0]);
        std::printf("%s\n", &(log[0]));
    }

    void GLSLProgram::printProgramInfoLog(GLuint a_ProgramID)
    {
        GLint maxLength = 0;
        glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> errorLog(maxLength);
        glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &errorLog[0]);
        std::printf("%s\n", &(errorLog[0]));
    }

    void GLSLProgram::setAsCurrent()
    {
        glUseProgram(m_ProgramID);
        for(int i = 0; i < m_AttributeCount; i++)
        {
            glEnableVertexAttribArray(i);
        }
    }

    void GLSLProgram::resetCurrent()
    {
        for(int i = 0; i < m_AttributeCount; i++)
        {
            glDisableVertexAttribArray(i);
        }
        glUseProgram(0);
    }
}