#pragma once
#include <glm/glm.hpp>

#include "Core/Component.h"

namespace BadEngine
{
    class Transform
    {
    public:
        glm::vec2 LocalPosition = glm::vec2(0.0f, 0.0f);
        float LocalRotation = 0.0f;
        const Transform* Parent = nullptr;

    public:
        Transform(glm::vec2 a_Position = glm::vec2(0.0f, 0.0f), float a_Rotation = 0.0f);
        ~Transform();

        void translate(glm::vec2 a_Translation);
        void rotate(float a_Angles);
        void lookAt(glm::vec2 a_Position);
        void setPosition(glm::vec2 a_Position);
        glm::vec2 getPosition() const;
        glm::vec2 getForward() const;
    };
}
