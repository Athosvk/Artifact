#pragma once
#include <GL/glew.h>
#include <vector>

namespace Artifact
{
    enum class EBufferUsage
    {
        Dynamic = GL_DYNAMIC_DRAW,
        Stream = GL_STREAM_DRAW,
        Static = GL_STATIC_DRAW
    };

    class IBO
    {
    private:
        GLuint m_ID = 0;
        EBufferUsage m_Usage;
        std::vector<GLuint> m_Data;

    public:
        IBO(EBufferUsage a_BufferUsage, const std::vector<GLuint>& a_InitialData = std::vector<GLuint>());
        ~IBO();

        void bind() const;
        void unbind() const;
        void draw(GLuint a_IndexCount, GLuint a_Offset) const;
        void setData(const std::vector<GLuint>& a_Data);

    private:
        void uploadData() const;
    };
}
