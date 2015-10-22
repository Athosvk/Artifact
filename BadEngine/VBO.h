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
        void setData(Vertex(&a_Data)[TSize]) const;
        void bind() const;
        void unbind() const;
    };
}
