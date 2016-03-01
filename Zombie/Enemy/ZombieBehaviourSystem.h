#pragma once
#include <Artifact/Core/System.h>
#include <glm/glm.hpp>

class ZombieBehaviourSystem : public Artifact::System
{
public:
    ZombieBehaviourSystem(Artifact::EntitySystem& a_EntitySystem, 
        Artifact::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void update();
    glm::vec2 getPlayerPosition() const;
};

