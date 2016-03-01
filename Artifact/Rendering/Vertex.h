#pragma once
#include <glm/glm.hpp>

#include "..\Color.h" 

namespace Artifact
{
    struct Vertex
    {
    public:
        glm::vec2 position = glm::vec2(0.0f, 0.0f);
        Color color;
        glm::vec2 uvCoordinate = glm::vec2(0.0f, 0.0f);

        Vertex(glm::vec2 a_Position, Color a_Color, glm::vec2 a_UVCoordinate)
            : position(a_Position), color(a_Color), uvCoordinate(a_UVCoordinate)
        {
            
        }

        Vertex()
        {
            
        }
    };
}