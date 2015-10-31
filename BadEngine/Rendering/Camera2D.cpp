#include "Camera2D.h"
#include "..\MathHelper.h"
#include "..\Input/Keyboard.h"

namespace BadEngine
{
    Camera2D::Camera2D(const Window& a_Window)
        : m_Window(a_Window)
    {
        constructMatrix();
    }

    Camera2D::~Camera2D()
    {
        
    }

    glm::vec2 Camera2D::getPosition() const
    {
        return m_Position;
    }

    float Camera2D::getZoomFactor() const
    {
        return m_ZoomFactor;
    }

    float Camera2D::getRotation() const
    {
        return m_Rotation;
    }

    glm::mat4 Camera2D::getTransform() const
    {
        return m_Transform;
    }

    glm::vec2 Camera2D::screenToWorld(glm::vec2 a_ScreenPosition) const
    {
        auto screenCenter = glm::vec2(static_cast<float>(m_Window.getWidth() / 2), 
                                      static_cast<float>(m_Window.getHeight() / 2));

        auto worldPosition = a_ScreenPosition - screenCenter;
        worldPosition /= m_ZoomFactor;

        auto angleCos = glm::cos(m_Rotation);
        auto angleSin = glm::sin(m_Rotation);
        worldPosition.x = angleCos * worldPosition.x - angleSin * worldPosition.y;
        worldPosition.y = angleSin * worldPosition.x + angleCos * worldPosition.y;
        worldPosition += m_Position;
        return worldPosition;
    }

    void Camera2D::setPosition(const glm::vec2& a_NewPosition)
    {
        m_Position = a_NewPosition;
        setMatrixDirty();
    }

    void Camera2D::setZoomFactor(float a_ZoomFactor)
    {
        //TO-DO: Restrict to positive values
        m_ZoomFactor = a_ZoomFactor;
        setMatrixDirty();
    }

    void Camera2D::setRotation(float a_Rotation)
    {
        m_Rotation = a_Rotation;
    }

    void Camera2D::update()
    {
        if(m_MatrixIsDirty)
        {
            constructMatrix();
        }

        updatePosition();
    }

    void Camera2D::constructMatrix()
    {
        //TO-DO: Seperate ortho construction to separate function
        auto screenWidth = static_cast<float>(m_Window.getWidth());
        auto screenHeight = static_cast<float>(m_Window.getHeight());
        
        m_OrthoMatrix = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight);
        m_Transform = m_OrthoMatrix;
        //Translate to screencenter for scaling/rotation
        auto screenCenter = glm::vec3(screenWidth / 2, screenHeight / 2, 0);
        m_Transform = glm::translate(m_Transform, screenCenter);

        applyRotation();
        applyScale();

        m_Transform = glm::translate(m_Transform, -screenCenter);

        auto translation = glm::vec3(-m_Position.x, -m_Position.y, 0);
        //Set the screencenter as origin
        m_Transform = glm::translate(m_Transform, translation + screenCenter);

        m_MatrixIsDirty = false;
    }

    void Camera2D::updatePosition()
    {
        if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::Down))
        {
            m_Position.y = BadEngine::MathHelper::clamp(m_Position.y - 15, -2000, 2000);
        }
        if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::Left))
        {
            m_Position.x = BadEngine::MathHelper::clamp(m_Position.x - 15, -2000, 2000);
        }
        if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::Right))
        {
            m_Position.x = BadEngine::MathHelper::clamp(m_Position.x + 15, -2000, 2000);
        }
        if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::Up))
        {
            m_Position.y = BadEngine::MathHelper::clamp(m_Position.y + 15, -2000, 2000);
        }

        if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::W))
        {
            m_ZoomFactor = BadEngine::MathHelper::clamp(m_ZoomFactor + 0.05f, 0.01f, 4.0f);
        }
        if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::S))
        {
            m_ZoomFactor = BadEngine::MathHelper::clamp(m_ZoomFactor - 0.05f, 0.01f, 4.0f);
        }
        if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::Q))
        {
            m_Rotation += 0.05f;
        }
        if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::E))
        {
            m_Rotation -= 0.05f;
        }
        if(BadEngine::Keyboard::isDown(BadEngine::KeyCode::Space))
        {
            m_Rotation = 0;
            m_ZoomFactor = 1;
            m_Position = glm::vec2(0, 0);
        }
        m_MatrixIsDirty = true;
    }

    void Camera2D::applyScale()
    {
        auto scale = glm::vec3(m_ZoomFactor, m_ZoomFactor, 1);
        m_Transform = glm::scale(m_Transform, scale);
    }

    void Camera2D::applyRotation()
    {
        auto rotationVector = glm::vec3(0, 0, 1);
        m_Transform = glm::rotate(m_Transform, m_Rotation, rotationVector);
    }

    void Camera2D::setMatrixDirty()
    {
        m_MatrixIsDirty = true;
    }
}