#pragma once
#include <BadEngine/Core/System.h>
#include <glm/glm.hpp>

class ZombieBehaviourSystem : public BadEngine::System
{
public:
    ZombieBehaviourSystem(BadEngine::EntitySystem& a_EntitySystem, 
        BadEngine::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void update();
    glm::vec2 getPlayerPosition() const;
};

