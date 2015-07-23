#include "Camera2D.h"

namespace BadEngine
{
    Camera2D::Camera2D(const Window* a_Window)
    {
        constructMatrix();
    }

    Camera2D::~Camera2D()
    {
    }

    void Camera2D::setPosition(const glm::vec2& a_NewPosition)
    {
        m_Position = a_NewPosition;
        setMatrixDirty();
    }

    glm::vec2 Camera2D::getPosition() const
    {
        return m_Position;
    }

    void Camera2D::setZoomFactor(float a_ZoomFactor)
    {
        m_ZoomFactor = a_ZoomFactor;
        setMatrixDirty();
    }

    float Camera2D::getZoomFactor() const
    {
        return m_ZoomFactor;
    }

    void Camera2D::setRotation(float a_Rotation)
    {
        m_Rotation = a_Rotation;
    }

    float Camera2D::getRotation() const
    {
        return m_Rotation;
    }

    glm::mat4 Camera2D::getTransform() const
    {
        return m_Transform;
    }

    void Camera2D::update()
    {
        if(m_MatrixIsDirty)
        {
            constructMatrix();
        }
    }

    void Camera2D::constructMatrix()
    {
        float screenWidth = static_cast<float>(Window::getCurrent()->getWidth());
        float screenHeight = static_cast<float>(Window::getCurrent()->getHeight());
        
        m_OrthoMatrix = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight);
        m_Transform = m_OrthoMatrix;

        glm::vec3 screenCentre = glm::vec3(screenWidth / 2, screenHeight / 2, 0);
        m_Transform = glm::translate(m_Transform, screenCentre);

        applyRotation(screenWidth, screenHeight);
        applyScale(screenWidth, screenHeight);

        glm::vec3 translation = glm::vec3(m_Position.x, m_Position.y, 0);
        m_Transform = glm::translate(m_Transform, translation);

        m_MatrixIsDirty = false;
    }

    void Camera2D::applyScale(float a_ScreenWidth, float a_ScreenHeight)
    {
        glm::vec3 scale = glm::vec3(m_ZoomFactor, m_ZoomFactor, 1);
        m_Transform = glm::scale(m_Transform, scale);
    }

    void Camera2D::applyRotation(float a_ScreenWidth, float a_ScreenHeight)
    {
        glm::vec3 rotationVector = glm::vec3(0, 0, 1);
        m_Transform = glm::rotate(m_Transform, m_Rotation, rotationVector);
    }

    void Camera2D::setMatrixDirty()
    {
        m_MatrixIsDirty = true;
    }
}