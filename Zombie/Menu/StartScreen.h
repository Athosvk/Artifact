#pragma once
#include <Artifact/Core/World.h>

namespace Artifact
{
    class AudioSource;
}

class StartScreen : public Artifact::World
{
private:
    Artifact::AudioSource* m_BackgroundMusic;

public:
    StartScreen(Artifact::GameTime& a_GameTime, Artifact::Game* a_CurrentGame);
    virtual ~StartScreen() override;

private:
    void handleInput();
};

