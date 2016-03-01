#pragma once
#include <Artifact/Core/System.h>

#include "HealthBar.h"

class PlayerComponent;

class HUDSystem : public Artifact::System
{
private:
    HealthBar m_HealthBar;
    Artifact::GameObject m_Text;

public:
    HUDSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void renderHUDComponents();
    PlayerComponent* getCurrentPlayer() const;
};