#include "GLTexture.h"

namespace BadEngine
{
    GLTexture::GLTexture(float a_Width, float a_Height) :
        m_Width(a_Width),
        m_Height(a_Height)
    {
        glGenTextures(1, &m_ID);
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

    GLuint GLTexture::getID() const
    {
        return m_ID;
    }
}