#include <glm/gtx/vector_angle.hpp>

#include "Transform.h"

Transform::Transform(glm::vec2 a_Position, float a_Rotation)
    : LocalPosition(a_Position),
    LocalRotation(a_Rotation)
{
}

Transform::~Transform()
{
}

void Transform::translate(glm::vec2 a_Translation)
{
    LocalPosition += a_Translation;
}

void Transform::rotate(float a_Angles)
{
    LocalRotation += a_Angles;
}

glm::vec2 Transform::getForward() const
{
    return glm::vec2(glm::cos(LocalRotation), glm::sin(LocalRotation));
}

void Transform::lookAt(glm::vec2 a_Position)
{
    LocalRotation = glm::angle(glm::normalize(a_Position - LocalPosition), glm::vec2(1, 0));
}

void Transform::setPosition(glm::vec2 a_Position)
{
    LocalPosition = a_Position;
    if(Parent)
    {
        LocalPosition -= Parent->getPosition();
    }
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