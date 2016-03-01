#pragma once
#include <Artifact/Core/Component.h>
#include <Artifact/Input/Keycode.h>

class PlayerInputComponent : public Artifact::Component
{
public:
    Artifact::KeyCode MoveUpKey;
    Artifact::KeyCode MoveDownKey;
    Artifact::KeyCode MoveLeftKey;
    Artifact::KeyCode MoveRightKey;

public:
    PlayerInputComponent(Artifact::GameObject a_GameObject);
};

