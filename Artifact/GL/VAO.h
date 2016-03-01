#pragma once
#include <GL/glew.h>

namespace Artifact
{
    class VAO
    {
    private:
        GLuint m_ID = 0;

    public:
        VAO();
        ~VAO();

        void bind() const;
        void unbind() const;
    };
}
