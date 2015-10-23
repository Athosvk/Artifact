#include <cstddef>
#include <string>
#include <glm/glm.hpp>

#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"
#include "GLSLProgram.h"
#include "Camera2D.h"

namespace BadEngine
{
    const std::string Sprite::s_DefaultVertexShader = "Vertex shaders/colorShading.vert";
    const std::string Sprite::s_DefaultFragmentShader = "Fragment shaders/colorShading.frag";

    Sprite::Sprite(const glm::vec2 a_Position,
                   const std::string a_TextureFilePath, const float a_Width, const float a_Height,
                   const std::string a_VertexShaderPath, const std::string a_FragmentShaderPath) :
        m_Position(a_Position),
        m_Texture(ResourceManager::getTexture(a_TextureFilePath)),
        m_ShaderProgram(GLSLProgram(a_VertexShaderPath, a_FragmentShaderPath)),
        m_Width(a_Width),
        m_Height(a_Height)
    {
        createVBO();
        initShaders();
    }

    Sprite::~Sprite()
    {
      
    }

    void Sprite::createVBO() const
    {
        Vertex vertexData[6];

        vertexData[0].position = glm::vec2(m_Position.x + m_Width, m_Position.y + m_Height);
        vertexData[0].uvCoordinate = glm::vec2(1.0f, 1.0f);

        vertexData[1].position = glm::vec2(m_Position.x, m_Position.y + m_Height);
        vertexData[1].uvCoordinate = glm::vec2(0.0f, 1.0f);

        vertexData[2].position = glm::vec2(m_Position.x, m_Position.y);
        vertexData[2].uvCoordinate = glm::vec2(0.0f, 0.0f);

        vertexData[3].position = glm::vec2(m_Position.x, m_Position.y);
        vertexData[3].uvCoordinate = glm::vec2(0.0f, 0.0f);

        vertexData[4].position = glm::vec2(m_Position.x + m_Width, m_Position.y);
        vertexData[4].uvCoordinate = glm::vec2(1.0f, 0.0f);

        vertexData[5].position = glm::vec2(m_Position.x + m_Width, m_Position.y + m_Height);
        vertexData[5].uvCoordinate = glm::vec2(1.0f, 1.0f);

        for(auto i = 0; i < 6; ++i)
        {
            vertexData[i].color = Color::White;
        }

        m_VBO.uploadData<6>(vertexData);
    }

    void Sprite::initShaders()
    {
        m_ShaderProgram.createAndCompileShaders();
        m_ShaderProgram.addAttribute("vertexPosition");
        m_ShaderProgram.addAttribute("vertexColor");
        m_ShaderProgram.addAttribute("vertexUVCoordinate");
        m_ShaderProgram.linkShaders();
    }

    void Sprite::draw(const Camera2D* a_Camera) const
    {
        m_ShaderProgram.enable();
        glActiveTexture(GL_TEXTURE0);

        auto textureLocation = m_ShaderProgram.getUniformLocation("sampler");
        glUniform1i(textureLocation, 0);

        auto cameraTransformLocation = m_ShaderProgram.getUniformLocation("cameraTransform");
        auto cameraTransform = a_Camera->getTransform();
        
        glUniformMatrix4fv(cameraTransformLocation, 1, GL_FALSE, &cameraTransform[0][0]);

        m_Texture.bind();
        m_VBO.bind();

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uvCoordinate)));

        glDrawArrays(GL_TRIANGLES, 0, 6);

        m_VBO.unbind();

        m_ShaderProgram.disable();
    }

    float Sprite::getWidth() const
    {
        return m_Width;
    }

    float Sprite::getHeight() const
    {
        return m_Height;
    }
}