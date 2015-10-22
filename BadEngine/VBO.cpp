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

    template<int TSize>
    void VBO::setData(Vertex(&a_Data)[TSize]) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_ID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(a_Data), a_Data, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
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