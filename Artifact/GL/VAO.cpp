#include "VAO.h"

namespace Artifact
{
    VAO::VAO()
    {
        glGenVertexArrays(1, &m_ID);
    }

    VAO::~VAO()
    {
        glDeleteVertexArrays(1, &m_ID);
    }

    void VAO::bind() const
    {
        glBindVertexArray(m_ID);
    }

    void VAO::unbind() const
    {
        glBindVertexArray(0);
    }
}