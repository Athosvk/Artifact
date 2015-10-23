#include "VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &m_ID);
}

VAO::~VAO()
{
}

void VAO::bind() const
{
    glBindVertexArray(m_ID);
}

void VAO::unbind() const
{
    glBindVertexArray(0);
}