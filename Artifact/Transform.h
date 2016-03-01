#pragma once
#include <glm/glm.hpp>
#include <memory>

#include "Core/Component.h"

namespace Artifact
{
    class Transform : public Component
    {
    private:
        glm::vec2 LocalPosition = glm::vec2(0.0f, 0.0f);
        float LocalRotation = 0.0f;
        const Transform* Parent = nullptr;
        glm::mat4 m_Matrix = glm::mat4(1.0f);
        bool m_Dirty = true;

    public:
        Transform(GameObject a_GameObject);

        void translate(glm::vec2 a_Translation);
        void rotate(float a_Angles);
        void lookAt(glm::vec2 a_Position);
        void setRotation(float a_Angles);
        void setPosition(glm::vec2 a_Position);
        void setLocalPosition(glm::vec2 a_LocalPosition);
        void setLocalRotation(float a_Angle);
        glm::vec2 getLocalPosition() const;
        float getLocalRotation() const;
        glm::vec2 getPosition() const;
        glm::vec2 getForward() const;
        float getRotation() const;
        glm::mat4& getMatrix();
        bool isDirty() const;
    private:
        void refreshMatrix();
    };
}
