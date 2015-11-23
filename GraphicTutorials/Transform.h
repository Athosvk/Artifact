#pragma once
#include <glm/glm.hpp>

class Transform
{
public:
    glm::vec2 Position = glm::vec2(0.0f, 0.0f);
    float Rotation;

public:
    Transform(glm::vec2 a_Position = glm::vec2(0.0f, 0.0f), float a_Rotation = 0.0f);
    ~Transform();

    void translate(glm::vec2 a_Translation);
    void rotate(float a_Angles);
    void lookAt(glm::vec2 a_Position);
    glm::vec2 getForward() const;
};

