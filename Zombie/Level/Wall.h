#pragma once
#include <Artifact/Core/GameObject.h>

namespace Artifact
{
    class GLTexture;
    class EntitySystem;
}

class Wall
{
private:
    Artifact::GameObject m_Entity;
    
public:
    Wall(Artifact::EntitySystem& a_EntitySystem, Artifact::GLTexture* a_Texture, glm::vec2 a_Dimensions);

    void setPosition(glm::vec2 a_Position);
};

