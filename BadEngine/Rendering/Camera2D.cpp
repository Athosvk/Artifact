#include "Camera2D.h"
#include "..\MathHelper.h"
#include "..\Input/Keyboard.h"

namespace BadEngine
{
    const int Camera2D::PixelsPerMeter = 100;

    Camera2D::Camera2D(const Window& a_Window)
        : m_Window(a_Window)
    {
        constructMatrix();
    }

    glm::vec2 Camera2D::getPosition() const
    {
        return m_Position;
    }

    void* Camera2D::operator new(std::size_t a_Size)
    {
        return _aligned_malloc(a_Size, 16);
    }

    void Camera2D::operator delete(void* a_Pointer)
    {
        _aligned_free(a_Pointer);
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

        auto worldPosition = glm::vec2(a_ScreenPosition.x, -a_ScreenPosition.y);
        worldPosition -= glm::vec2(screenCenter.x, -screenCenter.y);
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

    void Camera2D::applyScale()
    {
        auto scale = glm::vec3(m_ZoomFactor, m_ZoomFactor, 1) * static_cast<float>(PixelsPerMeter);
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