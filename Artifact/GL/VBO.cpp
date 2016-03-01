#include "VBO.h"

namespace Artifact
{
    VBO::VBO()
    {
        glGenBuffers(1, &m_ID);
    }

    VBO::~VBO()
    {
        glDeleteBuffers(1, &m_ID);
    }

    void VBO::uploadData(const std::vector<Vertex>& a_Data) const
    {
        bind();
        //Orphan the buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * a_Data.size(), nullptr, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * a_Data.size(), a_Data.data());
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