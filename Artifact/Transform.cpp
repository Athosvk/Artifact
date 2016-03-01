#include <glm/gtx/vector_angle.hpp>

#include "Transform.h"

namespace Artifact
{
    Transform::Transform(GameObject a_GameObject)
        : Component(a_GameObject)
    {
    }

    void Transform::translate(glm::vec2 a_Translation)
    {
        LocalPosition += a_Translation;
        m_Dirty = true;
    }

    void Transform::rotate(float a_Angles)
    {
        LocalRotation += a_Angles;
        m_Dirty = true;
    }

    glm::vec2 Transform::getForward() const
    {
        return glm::vec2(glm::cos(LocalRotation), glm::sin(LocalRotation));
    }

    void Transform::lookAt(glm::vec2 a_Position)
    {
        LocalRotation = glm::angle(glm::normalize(a_Position - LocalPosition), glm::vec2(1, 0));
        m_Dirty = true;
    }

    void Transform::setPosition(glm::vec2 a_Position)
    {
        LocalPosition = a_Position;
        if(Parent)
        {
            LocalPosition -= Parent->getPosition();
        }
        m_Dirty = true;
    }

    void Transform::setRotation(float a_Angles)
    {
        LocalRotation = a_Angles;
        if(Parent != nullptr)
        {
            LocalRotation -= Parent->getRotation();
        }
        m_Dirty = true;
    }

    void Transform::setLocalPosition(glm::vec2 a_LocalPosition)
    {
        LocalPosition = a_LocalPosition;
        m_Dirty = true;
    }

    void Transform::setLocalRotation(float a_Angle)
    {
        LocalRotation = a_Angle;
        m_Dirty = true;
    }

    glm::vec2 Transform::getLocalPosition() const
    {
        return LocalPosition;
    }

    float Transform::getLocalRotation() const
    {
        return LocalRotation;
    }

    glm::vec2 Transform::getPosition() const
    {
        glm::vec2 position = LocalPosition;
        if(Parent)
        {
            position += Parent->getPosition();
        }
        return position;
    }

    float Transform::getRotation() const
    {
        float rotation = LocalRotation;
        if(Parent)
        {
            rotation += Parent->getRotation();
        }
        return rotation;
    }

    glm::mat4& Transform::getMatrix()
    {
        if(m_Dirty)
        {
            refreshMatrix();
        }
        return m_Matrix;
    }

    bool Transform::isDirty() const
    {
        return m_Dirty;
    }

    void Transform::refreshMatrix()
    {
        m_Matrix = glm::mat4(1);
        m_Matrix = glm::translate(m_Matrix, glm::vec3(getPosition(), 0));
        glm::vec3 rotationNormal = glm::vec3(0, 0, 1);
        m_Matrix = glm::rotate(m_Matrix, getRotation(), rotationNormal);
        m_Dirty = false;
    }
}