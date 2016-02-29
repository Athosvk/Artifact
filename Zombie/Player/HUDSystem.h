#pragma once
#include <BadEngine/Core/System.h>

#include "HealthBar.h"

class PlayerComponent;

class HUDSystem : public BadEngine::System
{
private:
    HealthBar m_HealthBar;

public:
    HUDSystem(BadEngine::EntitySystem& a_EntitySystem, BadEngine::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void renderHUDComponents();
    PlayerComponent* getCurrentPlayer() const;
};