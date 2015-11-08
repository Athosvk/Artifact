#pragma once
#include <GL/glew.h>
#include <vector>

namespace BadEngine
{
    class GLTexture
    {
    private:
        GLuint m_ID = 0;
        float m_Width = 0.0f;
        float m_Height = 0.0f;

    public:
        GLTexture(float a_Width, float a_Height);
        ~GLTexture();

        bool operator >(const GLTexture& a_Other) const;
        bool operator <(const GLTexture& a_Other) const;
        bool operator >=(const GLTexture& a_Other) const;
        bool operator <=(const GLTexture& a_Other) const;
        bool operator ==(const GLTexture& a_Other) const;
        bool operator !=(const GLTexture& a_Other) const;

        void bind() const;
        void unbind() const;
        void uploadData(const std::vector<unsigned char>& a_Data) const;
    };
}