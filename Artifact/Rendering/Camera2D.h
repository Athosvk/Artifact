#pragma once
#include <glm/gtc/matrix_transform.hpp>

#include "../Core/Component.h"
#include "../Core/MessagingSystem.h"

namespace Artifact
{
    class Camera2D;

    class OnCameraChangedMessage : public Message
    {
    private:
        Camera2D* m_NewCamera;

    public:
        OnCameraChangedMessage(Camera2D* a_NewCamera);

        Camera2D* getNewCamera() const;
    };

    class Camera2D : public Component
    {
    public:
        static const int PixelsPerMeter;
    private:
        glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
        Transform* m_Transform;
        mutable bool m_Dirty = true;
        mutable glm::mat4 m_ViewProjection = glm::mat4(1.0f);
        mutable glm::mat4 m_InverseViewProjection = glm::mat4(1.0f);
        
    public:
        Camera2D(GameObject a_GameObject);
        
        const glm::mat4& getViewProjection() const;
        const glm::mat4& getInverseViewProjection() const;
        const glm::mat4& getProjectionMatrix() const;
        glm::vec2 screenToWorld(glm::vec2 a_ScreenPosition) const;

    private:
        void constructMatrix() const;
        void constructProjectionMatrix();
    };
}