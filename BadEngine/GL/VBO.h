#pragma once
#include <GL/glew.h>
#include <vector>

#include "../Rendering/Vertex.h"

namespace BadEngine
{
    class VBO
    {
    private:
        GLuint m_ID = 0;

    public:
        VBO();
        ~VBO();

        void uploadData(const std::vector<Vertex>& a_Data) const;
        void bind() const;
        void unbind() const;
    };
}
