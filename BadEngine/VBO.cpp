#include "VBO.h"

namespace BadEngine
{
    VBO::VBO()
    {
        glGenBuffers(1, &m_ID);
    }

    VBO::~VBO()
    {
        glDeleteBuffers(1, &m_ID);
    }

    void VBO::uploadData(Vertex* a_Data, unsigned int a_VertexCount) const
    {
        bind();
        //Orphan the buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * a_VertexCount, nullptr, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * a_VertexCount, a_Data);
        unbind();
    }

    void VBO::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    }

    void VBO::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}