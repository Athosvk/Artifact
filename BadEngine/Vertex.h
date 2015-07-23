#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Color.h" 
namespace BadEngine
{
    struct Vertex
    {
    public:
        glm::vec2 position = glm::vec2(0.0f, 0.0f);
        Color color = Color(0, 0, 0, 0);
        glm::vec2 uvCoordinate = glm::vec2(0.0f, 0.0f);
    };
}