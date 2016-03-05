#pragma once
#include <Artifact/Core/System.h>

#include "HealthBar.h"

class PlayerComponent;
namespace Artifact
{
    class TextComponent;
}

class HUDSystem : public Artifact::System
{
private:
    HealthBar m_HealthBar;
    Artifact::TextComponent* m_ScoreDisplay;

public:
    HUDSystem(Artifact::EntitySystem& a_EntitySystem, Artifact::MessagingSystem& a_MessagingSystem);

    virtual void registerListeners() override;
private:
    void updateHUDComponents();
    PlayerComponent* getCurrentPlayer() const;
};