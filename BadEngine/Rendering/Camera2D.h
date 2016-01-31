#pragma once
#include <glm/gtc/matrix_transform.hpp>

#include "../Core/Component.h"
#include "../Core/MessagingSystem.h"

namespace BadEngine
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
        mutable glm::mat4 m_InversViewProjection = glm::mat4(1.0f);
        
    public:
        Camera2D(GameObject a_GameObject);

        void* operator new(std::size_t a_Size);
        void operator delete(void* a_Pointer);
        
        float getZoomFactor() const;
        glm::mat4& getViewProjection() const;
        glm::mat4& getInverseViewProjection() const;
        glm::vec2 screenToWorld(glm::vec2 a_ScreenPosition) const;

    private:
        void constructMatrix() const;
        void constructProjectionMatrix();
    };
}