#include "IBO.h"

namespace Artifact
{
    IBO::IBO(EBufferUsage a_BufferUsage, const std::vector<GLuint>& a_InitialData)
        : m_Usage(a_BufferUsage),
        m_Data(a_InitialData)
    {
        glGenBuffers(1, &m_ID);
    }

    IBO::~IBO()
    {
        glDeleteBuffers(1, &m_ID);
    }

    void IBO::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    }

    void IBO::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IBO::uploadData() const
    {
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_Data.size(), nullptr, static_cast<GLenum>(m_Usage));
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLuint) * m_Data.size(), m_Data.data());
        unbind();
    }

    void IBO::draw(GLuint a_IndexCount, GLuint a_Offset) const
    {
        glDrawElements(GL_TRIANGLES, a_IndexCount, GL_UNSIGNED_INT, reinterpret_cast<void*>(a_Offset * sizeof(GLuint)));
    }

    void IBO::setData(const std::vector<GLuint>& a_Data)
    {
        m_Data = a_Data;
        uploadData();
    }
}