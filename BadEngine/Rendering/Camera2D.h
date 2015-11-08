#pragma once
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"

namespace BadEngine
{
    class Camera2D
    {
    private:
        glm::vec2 m_Position = glm::vec2(0.0f, 0.0f);
        float m_ZoomFactor = 1.0f;
        float m_Rotation = 0.0f;
        glm::mat4 m_Transform = glm::mat4(1.0f);
        glm::mat4 m_OrthoMatrix = glm::mat4(1.0f);
        bool m_MatrixIsDirty = false;
        
        const Window& m_Window;

    public:
        Camera2D(const Window& a_Window);
        ~Camera2D();

        Camera2D& operator=(const Camera2D& a_Other) = delete;

        glm::vec2 getPosition() const;
        float getZoomFactor() const;
        float getRotation() const;
        glm::mat4 getTransform() const;
        glm::vec2 screenToWorld(glm::vec2 a_ScreenPosition) const;
        void setPosition(const glm::vec2& a_NewPosition);
        void setZoomFactor(float a_ZoomFactor);
        void setRotation(float a_Rotation);
        void update();

    private:
        void setMatrixDirty();
        void constructMatrix();
        void updatePosition();
        void applyScale();
        void applyRotation();
    };
}