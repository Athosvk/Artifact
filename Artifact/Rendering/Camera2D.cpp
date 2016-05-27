#include "Camera2D.h"
#include "..\MathHelper.h"
#include "Window.h"

namespace Artifact
{
    OnCameraChangedMessage::OnCameraChangedMessage(ComponentHandle<Camera2D> a_NewCamera)
        : m_NewCamera(a_NewCamera)
    {
    }

    ComponentHandle<Camera2D> OnCameraChangedMessage::getNewCamera() const
    {
        return m_NewCamera;
    }

    const int Camera2D::PixelsPerMeter = 100;

    Camera2D::Camera2D(GameObject a_GameObject)
        : Component(a_GameObject),
		m_Transform(getComponent<Transform>())
    {
        constructProjectionMatrix();
        constructMatrix();
    }

    const glm::mat4& Camera2D::getViewProjection() const
    {
        if(m_Dirty || m_Transform->isDirty())
        {
            constructMatrix();
        }
        return m_ViewProjection;
    }

    const glm::mat4& Camera2D::getInverseViewProjection() const
    {
        if(m_Dirty || m_Transform->isDirty())
        {
            constructMatrix();
        }
        return m_InverseViewProjection;
    }

    const glm::mat4& Camera2D::getProjectionMatrix() const
    {
        return m_ProjectionMatrix;
    }

    void Camera2D::constructProjectionMatrix()
    {
        auto effectiveScreenWidth = static_cast<float>(Window::getWidth()) / PixelsPerMeter;
        auto effictiveScreenHeight = static_cast<float>(Window::getHeight()) / PixelsPerMeter;
        m_ProjectionMatrix = glm::ortho(-effectiveScreenWidth / 2, effectiveScreenWidth / 2,
                                        -effictiveScreenHeight / 2, effictiveScreenHeight / 2);
    }

    glm::vec2 Camera2D::screenToWorld(glm::vec2 a_ScreenPosition) const
    {
        auto normalizedScreenPosition = (a_ScreenPosition / glm::vec2(Window::getWidth(), 
            Window::getHeight())) * 2.0f - glm::vec2(1.0f, 1.0f);
        auto worldPosition = getInverseViewProjection() * glm::vec4(normalizedScreenPosition, 0, 1);
        return glm::vec2(worldPosition.x, worldPosition.y);
    }

    void Camera2D::constructMatrix() const
    {
        m_ViewProjection = m_Transform->getMatrix() * m_ProjectionMatrix;
        m_InverseViewProjection = glm::inverse(m_ViewProjection);
        m_Dirty = false;
    }
}