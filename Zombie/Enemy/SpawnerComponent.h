#pragma once
#include <glm/glm.hpp>

#include <Artifact/Core/Component.h>

class SpawnerComponent : public Artifact::Component
{
public:
    SpawnerComponent(Artifact::GameObject a_Entity);

    glm::vec2 getSpawnPosition() const;
};

