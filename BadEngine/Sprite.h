#pragma once
#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

#include "GLTexture.h"
#include "GLSLProgram.h"
#include "Camera2D.h"
#include "VBO.h"

namespace BadEngine
{
    class Sprite
    {
    protected:
        glm::vec2 m_Position;
        VBO m_VBO;
        GLTexture m_Texture;
        GLSLProgram m_ShaderProgram;
        float m_Width;
        float m_Height;

        static const std::string s_DefaultVertexShader;
        static const std::string s_DefaultFragmentShader;

    public:
        Sprite::Sprite(const glm::vec2 a_Position, const std::string a_TextureFilePath,
                       const float a_Width, const float a_Height,
                       const std::string a_VertexShaderPath = s_DefaultVertexShader, const std::string a_FragmentShaderPath = s_DefaultFragmentShader);        
        virtual ~Sprite();
        void draw(const Camera2D* a_Camera) const;

   protected:
        float getWidth() const;
        float getHeight() const;

    private:
        void createVBO() const;
        void initShaders();
    };
}
