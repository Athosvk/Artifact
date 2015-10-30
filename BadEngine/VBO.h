#pragma once
#include <GL/glew.h>

#include "Vertex.h"

namespace BadEngine
{
    class VBO
    {
    private:
        GLuint m_ID = 0;

    public:
        VBO();
        ~VBO();

        template<int TSize>
        void uploadData(Vertex(&a_Data)[TSize]) const
        {
            bind();
            //Orphan the buffer
            glBufferData(GL_ARRAY_BUFFER, sizeof(a_Data), nullptr, GL_DYNAMIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(a_Data), a_Data);
            unbind();
        }

        void uploadData(Vertex* a_Data, unsigned int a_VertexCount) const;
        void bind() const;
        void unbind() const;
    };
}
