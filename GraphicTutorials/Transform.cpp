#include <glm/gtx/vector_angle.hpp>

#include "Transform.h"

Transform::Transform(glm::vec2 a_Position, float a_Rotation)
    : Position(a_Position),
    Rotation(a_Rotation)
{
}

Transform::~Transform()
{
}

void Transform::translate(glm::vec2 a_Translation)
{
    Position += a_Translation;
}

void Transform::rotate(float a_Angles)
{
    Rotation += a_Angles;
}

glm::vec2 Transform::getForward() const
{
    return glm::vec2(glm::cos(Rotation), glm::sin(Rotation));
}

void Transform::lookAt(glm::vec2 a_Position)
{
    Rotation = glm::angle(glm::normalize(a_Position - Position), glm::vec2(1, 0));
}