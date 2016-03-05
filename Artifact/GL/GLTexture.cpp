#include "GLTexture.h"

namespace Artifact
{
    GLTexture::GLTexture(float a_Width, float a_Height) :
        m_Width(a_Width),
        m_Height(a_Height)
    {
        glGenTextures(1, &m_ID);
    }

    GLTexture::GLTexture(GLuint a_ID)
        : m_ID(a_ID)
    {
    }

    GLTexture::~GLTexture()
    {
        //IMPORTANT: Currenty commented out because cleaning up textures in a borderless window mode
        //will crash hard (i.e. the system loses control of the process and sign out or shut down is necessary)
        //Textures need no cleaning up at the moment, as they are not unused until the end of the program
        //Only uncomment this if you are aware of the possible consequences
        //glDeleteTextures(1, &m_ID);
    }

    bool GLTexture::operator <(const GLTexture& a_Other) const
    {
        return m_ID < a_Other.m_ID;
    }

    bool GLTexture::operator >(const GLTexture& a_Other) const
    {
        return m_ID > a_Other.m_ID;
    }

    bool GLTexture::operator <=(const GLTexture& a_Other) const
    {
        return m_ID <= a_Other.m_ID;
    }

    bool GLTexture::operator >=(const GLTexture& a_Other) const
    {
        return m_ID >= a_Other.m_ID;
    }

    bool GLTexture::operator ==(const GLTexture& a_Other) const
    {
        return m_ID == a_Other.m_ID;
    }

    bool GLTexture::operator !=(const GLTexture& a_Other) const
    {
        return m_ID != a_Other.m_ID;
    }

    void GLTexture::bind() const
    {
        glBindTexture(GL_TEXTURE_2D, m_ID);
    }

    void GLTexture::unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void GLTexture::uploadData(const std::vector<unsigned char>& a_Data) const
    {
        bind();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(m_Width), static_cast<GLsizei>(m_Height), 0, GL_RGBA, GL_UNSIGNED_BYTE, a_Data.data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
        unbind();
    }

    float GLTexture::getHeight() const
    {
        return m_Height;
    }

    float GLTexture::getWidth() const
    {
        return m_Width;
    }
}